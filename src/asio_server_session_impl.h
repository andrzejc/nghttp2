#ifndef ASIO_SERVER_SESSION_IMPL_H
#define ASIO_SERVER_SESSION_IMPL_H

#include "nghttp2_config.h"

#include "asio_server_http2_handler.h"

#include <nghttp2/asio_http2_server.h>

#include <boost/any.hpp>

namespace nghttp2 { namespace asio_http2 { namespace server {

class http2_handler;

struct session::impl {
  http2_handler& owner;
  session::create_cb on_create;
  session::close_cb on_close;
  boost::any user_data;

  explicit impl(http2_handler& owner, session::create_cb on_create):
    owner{owner},
    on_create{std::move(on_create)}
  {}

  void call_on_close() {
    if (on_close) {
      on_close(owner.api_, owner.stop_reason_);
    }
  }

  void call_on_create() {
    if (on_create) {
      on_create(owner.api_);
    }
  }
};

inline session::session(std::unique_ptr<impl> impl): impl_{std::move(impl)} {}
inline session::~session() = default;

} } }
#endif // ASIO_SERVER_SESSION_IMPL_H