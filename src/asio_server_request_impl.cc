/*
 * nghttp2 - HTTP/2 C Library
 *
 * Copyright (c) 2015 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "asio_server_request_impl.h"
#include "asio_server_stream.h"
#include "asio_server_http2_handler.h"
#include "asio_server_connection.h"

namespace nghttp2 {
namespace asio_http2 {
namespace server {

request_impl::request_impl() : strm_(nullptr), header_buffer_size_(0) {}

void request_impl::call_on_data(const uint8_t *data, std::size_t len) {
  if (on_data_cb_) {
    on_data_cb_(data, len);
  }
}

class session& request_impl::session() const {
  return strm_->handler()->session();
}

boost::posix_time::time_duration request_impl::read_timeout() const {
  return strm_->handler()->connection().read_timeout();
}

void request_impl::read_timeout(boost::posix_time::time_duration timeout) {
  strm_->handler()->connection().set_read_timeout(timeout);
}

} // namespace server
} // namespace asio_http2
} // namespace nghttp2
