#include <art/seafire/protocol/read.hxx>
#include <art/seafire/protocol/match.hxx>

#include <art/seafire/protocol/rfc7230/content-length.hxx>

#include <art/seafire/common/io/read-until.hxx>

#include <asio.hpp>

namespace art::seafire::protocol
{

  /// Read a request message from buffer \a b, reading more content from
  /// stream \a s as required.
  ///
  /// The read request message is placed in \a r.
  ///
  /// If the buffer \a b contains a full request message, no I/O operations
  /// will be performed.
  ///
  /// \throws std::system_error Thrown on error.
  /// \relatesalso request_t
  ///
  void
  read(common::io::stream_t& s,
       asio::streambuf& b,
       request_t& r)
  {
    std::error_code ec;
    read(s, b, r, ec);

    if (ec) {
      throw std::system_error{ec};
    }
  }

  /// Read a request message from buffer \a b, reading more content from
  /// stream \a s as required.
  ///
  /// The read request message is placed in \a r.
  ///
  /// If the buffer \a b contains a full request message, no I/O operations
  /// will be performed.
  ///
  /// Errors are reported through \a ec.
  ///
  /// \relatesalso request_t
  ///
  void
  read(common::io::stream_t& s,
       asio::streambuf& b,
       request_t& r,
       std::error_code& ec)
  {
    auto bytes_consumed = common::io::read_until(s, b, match_request_t{r}, ec);

    if (ec) {
      return;
    }

    b.consume(bytes_consumed);
  }

  /// Initialize an asynchronous read of a request message from buffer \a b,
  /// reading more content from \a s as required.
  ///
  /// The read request message is placed in \a r.
  ///
  /// If the buffer \a b contains a full request message, no I/O operations
  /// will be performed.
  ///
  /// \a r must be valid until the completion-handler \a h is called.
  ///
  void
  async_read(common::io::stream_t& s,
             asio::streambuf& b,
             request_t& r,
             std::function<void(std::error_code)> h)
  {
    auto bound = [&b, h](std::error_code const& ec, std::size_t n)
    {
      if (!ec) {
        b.consume(n);
      }

      h(ec);
    };

    common::io::async_read_until(s, b, match_request_t{r}, bound);
  }

  /// Read a response message from buffer \a b, reading more content from
  /// stream \a s as required.
  ///
  /// The read response message is placed in \a r.
  ///
  /// If the buffer \a b contains a full response message, no I/O operations
  /// will be performed.
  ///
  /// \throws std::system_error Thrown on error.
  /// \relatesalso response_t
  ///
  void
  read(common::io::stream_t& s,
       asio::streambuf& b,
       response_t& r)
  {
    std::error_code ec;
    read(s, b, r, ec);

    if (ec) {
      throw std::system_error{ec};
    }
  }

  /// Read a response message from buffer \a b, reading more content from
  /// stream \a s as required.
  ///
  /// The read response message is placed in \a r.
  ///
  /// If the buffer \a b contains a full response message, no I/O operations
  /// will be performed.
  ///
  /// Errors are reported through \a ec.
  ///
  /// \relatesalso response_t
  ///
  void
  read(common::io::stream_t& s,
       asio::streambuf& b,
       response_t& r,
       std::error_code& ec)
  {
    auto bytes_consumed = common::io::read_until(s, b, match_response_t{r}, ec);

    if (ec) {
      return;
    }

    b.consume(bytes_consumed);
  }

  /// Initialize an asynchronous read of a response message from buffer \a b,
  /// reading more content from \a s as required.
  ///
  /// The read response message is placed in \a r.
  ///
  /// If the buffer \a b contains a full response message, no I/O operations
  /// will be performed.
  ///
  /// \a r must be valid until the completion-handler \a h is called.
  ///
  void
  async_read(common::io::stream_t& s,
             asio::streambuf& b,
             response_t& r,
             std::function<void(std::error_code)> h)
  {
    auto bound = [&b, h](std::error_code const& ec, std::size_t n)
    {
      if (!ec) {
        b.consume(n);
      }

      h(ec);
    };

    common::io::async_read_until(s, b, match_response_t{r}, bound);
  }

} // namespace art::seafire::protocol
