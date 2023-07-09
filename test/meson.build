sources = [
#  'autobatch.cpp',
  'dev.cu.cpp',
  'graph.cpp',
#  'include.cpp',
  'model.cu.cpp',
  'nodes.cu.cpp',
  'nodes-common.cu.cpp',
  'nodes-compare.cu.cpp',
  'nodes-conv.cu.cpp',
  'nodes-dropout.cu.cpp',
  'nodes-inplace.cu.cpp',
  'nodes-layout.cu.cpp',
  'nodes-pick.cu.cpp',
  'nodes-pool.cu.cpp',
  'nodes-prod.cu.cpp',
  'nodes-reduce.cu.cpp',
  'sample.cpp',
  'tensor.cu.cpp',
  'util.cpp',
]

cuda_sources = [
  'dev.cu.cpp',
  'model.cu.cpp',
  'nodes.cu.cpp',
  'nodes-common.cu.cpp',
  'nodes-compare.cu.cpp',
  'nodes-conv.cu.cpp',
  'nodes-dropout.cu.cpp',
  'nodes-inplace.cu.cpp',
  'nodes-layout.cu.cpp',
  'nodes-pick.cu.cpp',
  'nodes-pool.cu.cpp',
  'nodes-prod.cu.cpp',
  'nodes-reduce.cu.cpp',
  'tensor.cu.cpp',
]

tests = []
cudatests = []

foreach src : sources
  exec_name = src.replace('.cu.cpp', '').replace('.cpp', '') + '-test'
  exe = executable(exec_name,
                   src,
                   include_directories : incdir,
                   dependencies : test_deps)
  tests += [exe]
  test(exec_name, exe)
endforeach

if gpu
  fs = import('fs')
  foreach src : cuda_sources
    exec_name = 'cuda-' + src.replace('.cu.cpp', '').replace('.cu', '') + '-test'
    copy_name = src.replace('.cu.cpp', '.copy.cu')
    copied_src = fs.copyfile(src, copy_name)

    if exec_name == 'cuda-nodes-conv-test'
      exe = executable(exec_name,
                      copied_src,
                      include_directories : incdir,
                      dependencies : test_deps + [cuda_dep],
                      cpp_args : cpp_args + ['-DGINN_ENABLE_GPU', '-g', '-O0'],
                      cuda_args : cuda_args + ['-DGINN_ENABLE_GPU', '-G', '-O0', '-Xptxas=-O0', '-Xcompiler=-Wno-maybe-uninitialized'])
    else
      exe = executable(exec_name,
                      copied_src,
                      include_directories : incdir,
                      dependencies : test_deps + [cuda_dep],
                      cpp_args : cpp_args + ['-DGINN_ENABLE_GPU'],
                      cuda_args : cuda_args + ['-DGINN_ENABLE_GPU'])
    endif

    tests += [exe]
    cudatests += [exe]
    test(exec_name, exe)
  endforeach
endif

alias_target('tests', tests)
if gpu
  alias_target('cudatests', cudatests)
endif
