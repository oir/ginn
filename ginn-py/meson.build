pymod = import('python')
py = pymod.find_installation('python3.9', required: false)

if py.found()
  pybind11 = subproject('pybind11').get_variable('pybind11_dep')

  sources = [
    'ginn-py.cpp',
    'dev-py.cpp',
    #    'tensor-py.cu.cpp',
    #    'node-py.cu.cpp',
    #    'node/affine-py.cu.cpp',
    #    'node/common-py.cu.cpp',
    #    'node/compare-py.cu.cpp',
    #    'node/nonlin-py.cu.cpp',
    #    'node/layout-py.cu.cpp',
    #    'node/pick-py.cu.cpp',
    #    'node/prod-py.cu.cpp',
    #    'node/reduce-py.cu.cpp',
    #    'node/select-py.cu.cpp',
    #    'node/weight-py.cu.cpp',
    #    'init-py.cu.cpp',
    #    'update-py.cu.cpp',
  ]

  gpu_sources = [
    'ginn-py.cu',
    'dev-py.cpp',
    'dev-py.cu',
  ]


  if gpu
    tgt = py.extension_module('ginn',
                              sources : gpu_sources,
                              include_directories : incdir,
                              dependencies : deps + [pybind11, cuda_dep],
                              cuda_args : cuda_args + ['-DGINN_ENABLE_GPU'])
  else
    tgt = py.extension_module('ginn',
                              sources : sources,
                              include_directories : incdir,
                              dependencies : deps + [pybind11])
  endif

  message('Python target name: ' + tgt.name())
  alias_target('python', tgt)
endif
