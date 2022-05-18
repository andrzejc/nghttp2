project('nghttp2', 'c', 'cpp',
  version: '1.48.0-dev',
  meson_version: '>=0.58.0',
  license: 'MIT',
  default_options: [
    'cpp_std=c++14',
    'default_library=static',
]
)

windows = host_machine.system() == 'windows'
cc = meson.get_compiler('c')
gcc = cc.get_argument_syntax() == 'gcc'
clang = cc.get_id().contains('clang')

cdata = configuration_data()

if cc.has_function_attribute('noreturn')
  cdata.set('NGHTTP2_NORETURN', '__attribute__((noreturn))')
endif

cdata.set('ssize_t',
  cc.has_type('ssize_t', prefix: '#include <sys/types.h>') ? 'ssize_t' : 'ptrdiff_t'
)

cdata.set('HAVE_STD_MAP_EMPLACE', 1)
cdata.set('HAVE_ATOMIC_STD_SHARED_PTR', 1)
cdata.set('HAVE_THREAD_LOCAL', 1)

# jansson_dep = dependency('jansson', required: false)
# if jansson_dep.found()
#   cdata.set('HAVE_JANSSON', 1)
# endif

# libxml2_dep = dependency('libxml2', required: false)
# if libxml2_dep.found()
#   cdata.set('HAVE_LIBXML2', 1)
# endif

# cdata.set('HAVE_MRUBY', 0)
# cdata.set('HAVE_NEVERBLEED', 0)

cdata.set('SIZEOF_INT_P', cc.sizeof('int*'))
cdata.set('SIZEOF_TIME_T', cc.sizeof('time_t', prefix: '#include <time.h>'))

checked_funcs = [
  ['_Exit', '<stdlib.h>'],
  ['accept4', '<sys/socket.h>'],
  ['mkostemp', '<stdlib.h>'],
]
foreach f: checked_funcs
  if (cc.has_function(f[0], prefix: '#define _GNU_SOURCE\n#include ' + f[1]))
    cdata.set('HAVE_' + f[0].underscorify().to_upper(), 1)
  endif
endforeach

if get_option('enable_debug_output')
  cdata.set('DEBUGBUILD', 1)
endif

# cdata.set('NOTHREADS', 0)

checked_headers = [
  'arpa/inet.h',
  'fcntl.h',
  'inttypes.h',
  'limits.h',
  'netdb.h',
  'netinet/in.h',
  'pwd.h',
  'sys/socket.h',
  'sys/time.h',
  'syslog.h',
  'time.h',
  'unistd.h',
]
foreach h: checked_headers
  if cc.has_header(h)
    cdata.set('HAVE_' + h.underscorify().to_upper(), 1)
  endif
endforeach

# cdata.set('ENABLE_HTTP3', 0)
# cdata.set('HAVE_LIBBPF', 0)
# cdata.set('HAVE_BPF_STATS_TYPE', 0)
# cdata.set('HAVE_LIBNGTCP2_CRYPTO_OPENSSL', 0)

if cc.has_member('struct tm', 'tm_gmtoff', prefix: '#include <time.h>')
  cdata.set('HAVE_STRUCT_TM_TM_GMTOFF', 1)
endif

cdata.set('PACKAGE_VERSION', meson.project_version())
version_sem = meson.project_version().split('-')[0].split('.')
version_num = version_sem[0].to_int() * 65536 + version_sem[1].to_int() * 256 + version_sem[2].to_int()
cdata.set('PACKAGE_VERSION_NUM', version_num)

configure_file(input: 'config.h.meson', output: 'config.h', configuration: cdata)
config_include = include_directories('.')

if windows
  add_project_arguments([
      '-D_CRT_SECURE_NO_WARNINGS',
      '-D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING',
      '-DNOMINMAX',
    ],
    language: ['c', 'cpp'],
  )
  ## REPETITIVE MESON SNIPPET BEGIN
  if clang and gcc
    # XXX this is only necessary for clang, not clang-cl, which meson treats as msvc
    use_debug_crt = get_option('buildtype') == 'debug'
    crt_opts_map = {
      'md': ['-D_MT', '-D_DLL'],
      'mdd': ['-D_MT', '-D_DLL', '-D_DEBUG'],
      'mt': ['-D_MT'],
      'mtd': ['-D_MT', '-D_DEBUG'],
      'from_buildtype': ['-D_MT', '-D_DLL'] + (use_debug_crt ? ['-D_DEBUG'] : []),
      'static_from_buildtype': ['-D_MT'] + (use_debug_crt ? ['-D_DEBUG'] : []),
    }
    crt_opts = crt_opts_map[get_option('clang_vscrt')]
    add_project_arguments(
      crt_opts + (
        get_option('debug') ? ['-Xclang', '-gcodeview'] : []
      ),
      language: ['c', 'cpp'],
    )
    if crt_opts.contains('-D_DLL')
      add_project_link_arguments(use_debug_crt ? [
          '-Wl,-nodefaultlib:libcmtd',
          '-lmsvcrtd',
        ] : [
          '-Wl,-nodefaultlib:libcmt',
          '-lmsvcrt',
        ],
        language: ['c', 'cpp'],
      )
    elif use_debug_crt
      add_project_link_arguments([
          '-Wl,-nodefaultlib:libcmt',
          '-llibcmtd',
        ],
        language: ['c', 'cpp'],
      )
    endif
    if get_option('b_sanitize') != 'none'
      if get_option('b_lto')
        warning('Option b_lto is known to cause ASAN odr-violation false postitives! (-Db_lto=false)')
      endif
      if crt_opts.contains('-D_DLL') or crt_opts.contains('-D_DEBUG')
        error('Sanitizer-enabled builds must use static release CRT (-Dclang_vscrt=mt)')
      endif
      # XXX workaround meson failing to provide linker option -fsanitize=... when compiler is clang
      add_project_link_arguments('-fsanitize=' + get_option('b_sanitize'), language: ['c', 'cpp'])
    endif
  endif
  ## REPETITIVE MESON SNIPPET END
endif

subdir('third-party')
subdir('lib')
subdir('src')