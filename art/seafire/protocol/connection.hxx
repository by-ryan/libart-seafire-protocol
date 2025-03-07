#ifndef art__seafire__protocol__connection_hxx_
#define art__seafire__protocol__connection_hxx_

#include <art/seafire/protocol/request.hxx>
#include <art/seafire/protocol/response.hxx>

#include <art/seafire/common/io/stream.hxx>

#include <asio.hpp>

#include <functional>
#include <system_error>

namespace art::seafire::protocol
{

  /// Implements an HTTP/1.0/1.1 connection.
  ///
  class connection_t
  {
  public:
    /// Asynchronous read handler type.
    ///
    using read_handler_t = std::function<void(std::error_code)>;

    /// Asynchronous write handler type.
    ///
    using write_handler_t = std::function<void(std::error_code)>;

    connection_t(common::io::stream_t&, std::size_t);

    connection_t(connection_t const&) = delete;
    connection_t(connection_t&&) = delete;

    ~connection_t() noexcept;

    common::io::stream_t&
    get_stream();

    asio::any_io_executor const&
    get_executor();

    void
    cancel();

    void
    read(request_t&, asio::streambuf&);

    void
    read(request_t&, asio::streambuf&, std::error_code&);

    void
    async_read(request_t&, asio::streambuf&, read_handler_t);

    void
    read(response_t&, asio::streambuf&);

    void
    read(response_t&, asio::streambuf&, std::error_code&);

    void
    async_read(response_t&, asio::streambuf&, read_handler_t);

    void
    write(request_t const&, common::io::const_buffers_t const&);

    void
    write(request_t const&, common::io::const_buffers_t const&, std::error_code&);

    void
    async_write(request_t const&, common::io::const_buffers_t const&, write_handler_t);

    void
    write(response_t const&, common::io::const_buffers_t const&);

    void
    write(response_t const&, common::io::const_buffers_t const&, std::error_code&);

    void
    async_write(response_t const&, common::io::const_buffers_t const&, write_handler_t);

    connection_t& operator=(connection_t const&) = delete;
    connection_t& operator=(connection_t&&) = delete;

  private:
    common::io::stream_t& stream_;
    asio::streambuf buffer_;

  };

} // namespace art::seafire::protocol

#endif
