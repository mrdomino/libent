project('libent', 'c', version: '0.2.2', license: 'MIT')

inc = include_directories('include')

subdir('src')

libent_dep = declare_dependency(
  include_directories: inc,
  link_with: libent,
)

ent_sample = executable(
  'sample',
  ['sample.c'],
  dependencies: [libent_dep],
)

if get_option('ent_install')
  pkg = import('pkgconfig')
  pkg.generate(
    libraries: [libent],
    name: 'libent',
    description: 'getentropy shim',
  )
  install_headers('include/ent.h')
endif
