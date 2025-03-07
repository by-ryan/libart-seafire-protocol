#ifndef art__seafire__protocol__read_hxx_
#define art__seafire__protocol__read_hxx_

#include <art/seafire/protocol/message.hxx>
#include <art/seafire/protocol/request.hxx>
#include <art/seafire/protocol/response.hxx>

#include <art/seafire/common/io/stream.hxx>

#include <asio.hpp>

#include <cstddef>
#include <system_error>

namespace art::seafire::protocol
{

  void
  read(common::io::stream_t&,
       asio::streambuf&,
       request_t&);

  void
  read(common::io::stream_t&,
       asio::streambuf&,
       request_t&,
       std::error_code&);

  void
  async_read(common::io::stream_t&,
             asio::streambuf&,
             request_t&,
             std::function<void(std::error_code)>);

  void
  read(common::io::stream_t&,
       asio::streambuf&,
       response_t&);

  void
  read(common::io::stream_t&,
       asio::streambuf&,
       response_t&,
       std::error_code&);

  void
  async_read(common::io::stream_t&,
             asio::streambuf&,
             response_t&,
             std::function<void(std::error_code)>);

} // namespace art::seafire::protocol

#endif
