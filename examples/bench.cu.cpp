// Copyright 2022 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <ginn/dev.h>
#include <ginn/node/affine.h>
// #include <ginn/node/layout.h>
// #include <ginn/nonlin.h>
#include <ginn/prod.h>
#include <ginn/tensor.h>
#include <ginn/util/cli2.h>
#include <ginn/util/fmt.h>
#include <ginn/util/parfor.h>
#include <ginn/util/timer.h>
#include <iostream>

#ifdef GINN_ENABLE_GPU
#include <cublasLt.h>

void LtSgemm(cublasLtHandle_t ltHandle,
             cublasOperation_t transa,
             cublasOperation_t transb,
             int m,
             int n,
             int k,
             const float* alpha, /* host pointer */
             const float* A,
             int lda,
             const float* B,
             int ldb,
             const float* beta, /* host pointer */
             float* C,
             int ldc,
             void* workspace,
             size_t workspaceSize) {
  cublasLtMatmulDesc_t operationDesc = NULL;
  cublasLtMatrixLayout_t Adesc = NULL, Bdesc = NULL, Cdesc = NULL;
  cublasLtMatmulPreference_t preference = NULL;

  int returnedResults = 0;
  cublasLtMatmulHeuristicResult_t heuristicResult = {};

  // create operation desciriptor; see cublasLtMatmulDescAttributes_t for
  // details about defaults; here we just need to set the transforms for A and B
  GINN_CUBLAS_CALL(
      cublasLtMatmulDescCreate(&operationDesc, CUBLAS_COMPUTE_32F, CUDA_R_32F));
  GINN_CUBLAS_CALL(cublasLtMatmulDescSetAttribute(
      operationDesc, CUBLASLT_MATMUL_DESC_TRANSA, &transa, sizeof(transa)));
  GINN_CUBLAS_CALL(cublasLtMatmulDescSetAttribute(
      operationDesc, CUBLASLT_MATMUL_DESC_TRANSB, &transb, sizeof(transa)));

  // create matrix descriptors, we are good with the details here so no need to
  // set any extra attributes
  GINN_CUBLAS_CALL(cublasLtMatrixLayoutCreate(&Adesc,
                                              CUDA_R_32F,
                                              transa == CUBLAS_OP_N ? m : k,
                                              transa == CUBLAS_OP_N ? k : m,
                                              lda));
  GINN_CUBLAS_CALL(cublasLtMatrixLayoutCreate(&Bdesc,
                                              CUDA_R_32F,
                                              transb == CUBLAS_OP_N ? k : n,
                                              transb == CUBLAS_OP_N ? n : k,
                                              ldb));
  GINN_CUBLAS_CALL(cublasLtMatrixLayoutCreate(&Cdesc, CUDA_R_32F, m, n, ldc));

  // create preference handle; here we could use extra attributes to disable
  // tensor ops or to make sure algo selected will work with badly aligned A, B,
  // C; here for simplicity we just assume A,B,C are always well aligned (e.g.
  // directly come from cudaMalloc)
  GINN_CUBLAS_CALL(cublasLtMatmulPreferenceCreate(&preference));
  GINN_CUBLAS_CALL(cublasLtMatmulPreferenceSetAttribute(
      preference,
      CUBLASLT_MATMUL_PREF_MAX_WORKSPACE_BYTES,
      &workspaceSize,
      sizeof(workspaceSize)));

  // we just need the best available heuristic to try and run matmul. There is
  // no guarantee this will work, e.g. if A is badly aligned, you can request
  // more (e.g. 32) algos and try to run them one by one until something works
  GINN_CUBLAS_CALL(cublasLtMatmulAlgoGetHeuristic(ltHandle,
                                                  operationDesc,
                                                  Adesc,
                                                  Bdesc,
                                                  Cdesc,
                                                  Cdesc,
                                                  preference,
                                                  1,
                                                  &heuristicResult,
                                                  &returnedResults));

  if (returnedResults == 0) {
    // GINN_CUBLAS_CALL(CUBLAS_STATUS_NOT_SUPPORTED);
    GINN_THROW("cublas status not supported");
  }

  GINN_CUBLAS_CALL(cublasLtMatmul(ltHandle,
                                  operationDesc,
                                  alpha,
                                  A,
                                  Adesc,
                                  B,
                                  Bdesc,
                                  beta,
                                  C,
                                  Cdesc,
                                  C,
                                  Cdesc,
                                  &heuristicResult.algo,
                                  workspace,
                                  workspaceSize,
                                  0));

  // descriptors are no longer needed as all GPU work was already enqueued
  if (preference) GINN_CUBLAS_CALL(cublasLtMatmulPreferenceDestroy(preference));
  if (Cdesc) GINN_CUBLAS_CALL(cublasLtMatrixLayoutDestroy(Cdesc));
  if (Bdesc) GINN_CUBLAS_CALL(cublasLtMatrixLayoutDestroy(Bdesc));
  if (Adesc) GINN_CUBLAS_CALL(cublasLtMatrixLayoutDestroy(Adesc));
  if (operationDesc) GINN_CUBLAS_CALL(cublasLtMatmulDescDestroy(operationDesc));
}
#endif

using namespace ginn;

void barrier() {
#ifdef GINN_ENABLE_GPU
  // This is needed for proper timing since cuda calls are async and cpu code
  // continues execution immediately.
  for (int i = 0; i < gpus(); i++) {
    GINN_CUDA_CALL(cudaSetDevice(i));
    GINN_CUDA_CALL(cudaDeviceSynchronize());
  }
#endif
}

void affine() {
#ifdef GINN_ENABLE_GPU
  auto dev = gpu();
  Tensor<Real, GPU> sink(dev, Shape{});
  sink.set_zero();
  Tensor<Real, GPU> dummy(sink);
  internal::gpu_prod(
      sink, dummy, dummy); // first prod is always slow. JIT? Cublas init?
  size_t num_repeat = 1e3;
#else
  auto dev = cpu();
  size_t num_repeat = 3;
#endif
  barrier();

  for (Size hdim : {1024, 2048}) {
    for (Size batches : {1024, 2048}) {
      // for (Size hdim : {1, 10, 100, 250, 500, 1000, 4000}) {
      //   for (Size batches : {1, 10, 100, 250, 500, 1000, 4000, 16000}) {
      for (size_t i = 0; i < num_repeat; i++) {
        auto x = Data<Real>(dev, Shape{hdim, batches});
        auto W = Data<Real>(dev, Shape{batches, hdim});
        auto b = Data<Real>(dev, Shape{batches});
        for (auto n : {x, W, b}) { n->value().set_random(); }
        auto y = Affine(W, x, b);
        Graph g(y);

        std::string prefix =
            std::to_string(hdim) + ";" + std::to_string(batches);

        timer::time(prefix + " fwd", [&]() {
          g.forward();
          barrier();
        });
        // timer::time(prefix + " rg", [&]() {
        //   g.reset_grad();
        //   barrier();
        // });
        // timer::time(prefix + " bwd", [&]() {
        //   g.backward(1.);
        //   barrier();
        // });
      }
    }
  }

  timer::print(timer::TimerSort::Name);
  timer::reset();
}

int main(int argc, char** argv) {
  using namespace ginn;

  std::unordered_map<std::string, void (*)()> benchmarks{
      //     {"cpu-matmul", compare_cpu_matmuls},
      //     {"gelu", compare_gelus},
      {"affine", affine},
      //     {"matmul", compare_matmuls},
      //     {"multi-gpu", multi_gpu},
  };

  std::vector<std::string> keys;
  for (auto& p : benchmarks) { keys.push_back(p.first); }

  std::vector<std::string> names;

  Args args;
  args(Arg(names)
           .meta("benchmark name")
           .help("name(s) of the benchmarks to run")
           .required()
           .require_choices(keys));
  args.parse(argc, argv);

  for (const auto& name : names) {
    std::cout << "Running benchmark: " << name << "..." << std::endl;
    benchmarks[name]();
  }

  return 0;
}
