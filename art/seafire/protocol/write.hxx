#ifndef art__seafire__protocol__write_hxx_
#define art__seafire__protocol__write_hxx_

#include <art/seafire/protocol/request.hxx>
#include <art/seafire/protocol/response.hxx>

#include <art/seafire/common/io/buffer.hxx>
#include <art/seafire/common/io/stream.hxx>

#include <asio.hpp>

#include <functional>
#include <system_error>

namespace art::seafire::protocol
{

  void
  write(common::io::stream_t&,
        request_t const&);

  void
  write(common::io::stream_t&,
        request_t const&,
        std::error_code&);

  void
  write(common::io::stream_t&,
        request_t const&,
        std::vector<common::io::const_buffer_t> const&);

  void
  write(common::io::stream_t&,
        request_t const&,
        std::vector<common::io::const_buffer_t> const&,
        std::error_code&);

  void
  async_write(common::io::stream_t&,
              request_t const&,
              std::function<void(std::error_code)>);

  void
  async_write(common::io::stream_t&,
              request_t const&,
              std::vector<common::io::const_buffer_t> const&,
              std::function<void(std::error_code)>);

  void
  write(common::io::stream_t&,
        response_t const&);

  void
  write(common::io::stream_t&,
        response_t const&,
        std::error_code&);

  void
  write(common::io::stream_t&,
        response_t const&,
        std::vector<common::io::const_buffer_t> const&);

  void
  write(common::io::stream_t&,
        response_t const&,
        std::vector<common::io::const_buffer_t> const&,
        std::error_code&);

  void
  async_write(common::io::stream_t&,
              response_t const&,
              std::function<void(std::error_code)>);

  void
  async_write(common::io::stream_t&,
              response_t const&,
              std::vector<common::io::const_buffer_t> const&,
              std::function<void(std::error_code)>);

} // namespace art::seafire::protocol

#endif
