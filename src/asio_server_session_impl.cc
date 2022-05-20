#include "asio_server_session_impl.h"

namespace nghttp2 { namespace asio_http2 { namespace server {
void session::on_close(close_cb cb) {
  impl_->on_close = std::move(cb);
}

void session::user_data(boost::any any) {
    impl_->user_data = std::move(any);
}

const boost::any& session::user_data() const {
    return impl_->user_data;
}

const boost::asio::ip::tcp::endpoint& session::remote_endpoint() const {
  return impl_->owner.remote_endpoint();
}

session::native_handle_type session::native_handle() {
  return impl_->owner.session_;
}
} } }
