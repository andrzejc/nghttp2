boost_dep = dependency('boost',
  static: true,
  required: true,
  include_type: 'system',
  modules: ['system', 'thread'],
)

openssl_dep = dependency('openssl', static: true, required: true, include_type: 'system')

nghttp2_asio_lib = library('nghttp2_asio', [
    'util.cc',
    'http2.cc',
    'tls.cc',
    'timegm.c',
    'asio_common.cc',
    'asio_server_http2.cc',
    'asio_server_http2_impl.cc',
    'asio_server.cc',
    'asio_server_http2_handler.cc',
    'asio_server_request.cc',
    'asio_server_request_impl.cc',
    'asio_server_response.cc',
    'asio_server_response_impl.cc',
    'asio_server_session_impl.cc',
    'asio_server_stream.cc',
    'asio_server_serve_mux.cc',
    'asio_server_request_handler.cc',
    'asio_server_tls_context.cc',
    'asio_client_session.cc',
    'asio_client_session_impl.cc',
    'asio_client_session_tcp_impl.cc',
    'asio_client_session_tls_impl.cc',
    'asio_client_response.cc',
    'asio_client_response_impl.cc',
    'asio_client_request.cc',
    'asio_client_request_impl.cc',
    'asio_client_stream.cc',
    'asio_client_tls_context.cc',
  ] + (
    windows ? ['../third-party/wingetopt/src/getopt.c'] : []
  ),
  dependencies: [
    boost_dep,
    openssl_dep,
    nghttp2_dep,
    url_parser_dep,
    llhttp_dep,
  ],
  cpp_args: '-DHAVE_CONFIG_H',
  c_args: '-DHAVE_CONFIG_H',
  include_directories: [
    config_include,
    include_directories('includes', '../third-party'),
  ] + (
    windows ? ['../third-party/wingetopt/src'] : []
  ),
)

nghttp2_asio_dep = declare_dependency(
  link_with: nghttp2_asio_lib,
  include_directories: include_directories('includes'),
  dependencies: [nghttp2_dep, boost_dep],
)