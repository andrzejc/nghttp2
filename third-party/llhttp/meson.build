llhttp_dep = declare_dependency(
  link_with: static_library('llhttp', 'src/api.c', 'src/http.c', 'src/llhttp.c',
    include_directories: include_directories('include'),
    c_args: '-Wno-unused-variable',
  ),
  include_directories: include_directories('include'),
)