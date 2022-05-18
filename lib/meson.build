subdir('includes/nghttp2')

nghttp2_lib = library('nghttp2', [
    'nghttp2_pq.c',
    'nghttp2_map.c',
    'nghttp2_queue.c',
    'nghttp2_frame.c',
    'nghttp2_buf.c',
    'nghttp2_stream.c',
    'nghttp2_outbound_item.c',
    'nghttp2_session.c',
    'nghttp2_submit.c',
    'nghttp2_helper.c',
    'nghttp2_npn.c',
    'nghttp2_hd.c',
    'nghttp2_hd_huffman.c',
    'nghttp2_hd_huffman_data.c',
    'nghttp2_version.c',
    'nghttp2_priority_spec.c',
    'nghttp2_option.c',
    'nghttp2_callbacks.c',
    'nghttp2_mem.c',
    'nghttp2_http.c',
    'nghttp2_rcbuf.c',
    'nghttp2_debug.c',
  ],
  c_args: [
    '-DHAVE_CONFIG_H',
    get_option('default_library') == 'static' ? '-DNGHTTP2_STATICLIB' : '-DBUILDING_NGHTTP2',
  ],
  include_directories: [
    config_include,
    include_directories('includes'),
  ],
)

nghttp2_dep = declare_dependency(
  link_with: nghttp2_lib,
  include_directories: include_directories('includes'),
  compile_args: get_option('default_library') == 'static' ? ['-DNGHTTP2_STATICLIB'] : [],
)