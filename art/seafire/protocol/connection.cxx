#include <art/seafire/protocol/connection.hxx>

#include <art/seafire/protocol/read.hxx>
#include <art/seafire/protocol/read-content.hxx>
#include <art/seafire/protocol/write.hxx>

#include <art/seafire/protocol/rfc7230/content-length.hxx>

namespace art::seafire::protocol
{

  /// Construct a new HTTP connection.
  ///
  /// \param s The I/O stream.
  /// \param max The maximum size of the connection buffer.
  ///
  connection_t::
  connection_t(common::io::stream_t& s, std::size_t max)
    : stream_{s},
      buffer_{max}
  {}

  /// Destroy this connection.
  ///
  connection_t::
  ~connection_t() noexcept = default;

  /// Access the underlying I/O stream.
  ///
  common::io::stream_t&
  connection_t::
  get_stream()
  {
    return stream_;
  }

  asio::any_io_executor const&
  connection_t::
  get_executor()
  {
    return get_stream().get_executor();
  }

  void
  connection_t::
  cancel()
  {
    get_stream().cancel();
  }

  /// Perform a blocking read of a request.
  ///
  /// \param r       The target request object.
  /// \param content The target request content buffer.
  /// \throws std::system_error Thrown on error.
  ///
  void
  connection_t::
  read(request_t& r, asio::streambuf& content)
  {
    protocol::read(get_stream(), buffer_, r);
    read_content(get_stream(), buffer_, content, r);
  }

  /// Perform a blocking read of a request.
  ///
  /// \param r       The target request object.
  /// \param content The target request content buffer.
  ///
  void
  connection_t::
  read(request_t& r,
       asio::streambuf& content,
       std::error_code& ec)
  {
    protocol::read(get_stream(), buffer_, r, ec);

    if (ec) {
      return;
    }

    read_content(get_stream(), buffer_, content, r, ec);
  }

  /// Initiate an non-blocking read of a request.
  ///
  /// \param r       The target request object.
  /// \param content The target request content buffer.
  /// \param handler The handler to invoke on completion.
  ///
  void
  connection_t::
  async_read(request_t& r,
             asio::streambuf& content,
             read_handler_t handler)
  {
    auto bound = [this, &r, &content, handler](std::error_code const& ec)
    {
      if (ec) {
        handler(ec);
        return;
      }

      async_read_content(get_stream(), buffer_, content, r, handler);
    };

    protocol::async_read(get_stream(), buffer_, r, bound);
  }

  /// Perform a blocking read of a response.
  ///
  /// \param r       The target response object.
  /// \param content The target response content buffer.
  /// \throws std::system_error Thrown on error.
  ///
  void
  connection_t::
  read(response_t& r, asio::streambuf& content)
  {
    protocol::read(get_stream(), buffer_, r);
    read_content(get_stream(), buffer_, content, r);
  }

  /// Perform a blocking read of a response.
  ///
  /// \param r       The target response object.
  /// \param content The target response content buffer.
  ///
  void
  connection_t::
  read(response_t& r,
       asio::streambuf& content,
       std::error_code& ec)
  {
    protocol::read(get_stream(), buffer_, r, ec);

    if (ec) {
      return;
    }

    read_content(get_stream(), buffer_, content, r, ec);
  }

  /// Initiate an non-blocking read of a response.
  ///
  /// \param r       The target response object.
  /// \param content The target response content buffer.
  /// \param handler The handler to invoke on completion.
  ///
  void
  connection_t::
  async_read(response_t& r,
             asio::streambuf& content,
             read_handler_t handler)
  {
    auto bound = [this, &r, &content, handler](std::error_code const& ec)
    {
      if (ec) {
        handler(ec);
        return;
      }

      async_read_content(get_stream(), buffer_, content, r, handler);
    };

    protocol::async_read(get_stream(), buffer_, r, bound);
  }

  /// Initiate a blocking write of a request message.
  ///
  void
  connection_t::
  write(request_t const& r, common::io::const_buffers_t const& content)
  {
    protocol::write(get_stream(), r, content);
  }

  /// Initiate a blocking write of a request message.
  ///
  void
  connection_t::
  write(request_t const& r, common::io::const_buffers_t const& content, std::error_code& ec)
  {
    protocol::write(get_stream(), r, content, ec);
  }

  /// Initiate a non-blocking write of a request message.
  ///
  void
  connection_t::
  async_write(request_t const& r, common::io::const_buffers_t const& content, write_handler_t handler)
  {
    protocol::async_write(get_stream(), r, content, handler);
  }

  void
  connection_t::
  write(response_t const& r, common::io::const_buffers_t const& content)
  {
    protocol::write(get_stream(), r, content);
  }

  void
  connection_t::
  write(response_t const& r, common::io::const_buffers_t const& content, std::error_code& ec)
  {
    protocol::write(get_stream(), r, content, ec);
  }

  void
  connection_t::
  async_write(response_t const& r, common::io::const_buffers_t const& content, write_handler_t handler)
  {
    protocol::async_write(get_stream(), r, content, handler);
  }

} // namespace art::seafire::protocol
