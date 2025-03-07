#ifndef art__seafire__protocol__read_content_hxx_
#define art__seafire__protocol__read_content_hxx_

#include <art/seafire/protocol/request.hxx>
#include <art/seafire/protocol/response.hxx>

#include <art/seafire/common/io/stream.hxx>

namespace art::seafire::protocol
{

  void
  read_content(common::io::stream_t&,
               asio::streambuf&,
               asio::streambuf&,
               std::size_t);

  void
  read_content(common::io::stream_t&,
               asio::streambuf&,
               asio::streambuf&,
               std::size_t,
               std::error_code&);

  void
  async_read_content(common::io::stream_t&,
                     asio::streambuf&,
                     asio::streambuf&,
                     std::size_t,
                     std::function<void(std::error_code)>);

  void
  read_content(common::io::stream_t&,
               asio::streambuf&,
               asio::streambuf&,
               request_t const&);

  void
  read_content(common::io::stream_t&,
               asio::streambuf&,
               asio::streambuf&,
               request_t const&,
               std::error_code&);

  void
  async_read_content(common::io::stream_t&,
                     asio::streambuf&,
                     asio::streambuf&,
                     request_t const&,
                     std::function<void(std::error_code)>);

  void
  read_content(common::io::stream_t&,
               asio::streambuf&,
               asio::streambuf&,
               response_t const&);

  void
  read_content(common::io::stream_t&,
               asio::streambuf&,
               asio::streambuf&,
               response_t const&,
               std::error_code&);

  void
  async_read_content(common::io::stream_t&,
                     asio::streambuf&,
                     asio::streambuf&,
                     response_t const&,
                     std::function<void(std::error_code)>);

} // namespace art::seafire::protocol

#endif
