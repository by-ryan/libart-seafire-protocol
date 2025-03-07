#include <art/seafire/protocol/read-content.hxx>

#include <art/seafire/protocol/rfc7230/content-length.hxx>

namespace art::seafire::protocol
{

  void
  read_content(common::io::stream_t& s,
               asio::streambuf& i,
               asio::streambuf& c,
               std::size_t content_length)
  {
    std::error_code ec;
    read_content(s, i, c, content_length, ec);

    if (ec) {
      throw std::system_error{ec};
    }
  }

  void
  read_content(common::io::stream_t& s,
               asio::streambuf& i,
               asio::streambuf& c,
               std::size_t content_length,
               std::error_code& ec)
  {
    if (auto pending = i.size(); pending > 0) {
      auto copied = buffer_copy(
        c.prepare(pending),
        i.data(),
        std::min<std::size_t>(pending, content_length)
      );
      i.consume(copied);
      c.commit(copied);
      content_length -= copied;
    }

    auto n = s.read(c.prepare(content_length), ec);
    c.commit(n);
  }

  void
  async_read_content(common::io::stream_t& s,
                     asio::streambuf& i,
                     asio::streambuf& c,
                     std::size_t content_length,
                     std::function<void(std::error_code)> h)
  {
    if (auto pending = i.size(); pending > 0) {
      auto copied = buffer_copy(
        c.prepare(pending),
        i.data(),
        std::min<std::size_t>(pending, content_length)
      );

      i.consume(copied);
      c.commit(copied);
      content_length -= copied;
    }

    auto bound = [&c, h](std::error_code const& ec, std::size_t n)
    {
      c.commit(n);
      h(ec);
    };

    s.async_read(c.prepare(content_length), bound);
  }

  /// Read content from stream.
  ///
  void
  read_content(common::io::stream_t& s,
               asio::streambuf& i,
               asio::streambuf& c,
               request_t const& r)
  {
    std::error_code ec;
    read_content(s, i, c, r, ec);

    if (ec) {
      throw std::system_error{ec};
    }
  }

  void
  read_content(common::io::stream_t& s,
               asio::streambuf& i,
               asio::streambuf& c,
               request_t const& r,
               std::error_code& ec)
  {
    // fixme: support transfer encoding.
    //

    auto content_length = get<rfc7230::content_length_t>(r, ec);

    if (ec) {
      return;
    }

    if (content_length) {
      read_content(s, i, c, *content_length, ec);
      return;
    }

    // we just assume the message does not contain a payload.
    //
  }

  void
  async_read_content(common::io::stream_t& s,
                     asio::streambuf& i,
                     asio::streambuf& c,
                     request_t const& r,
                     std::function<void(std::error_code)> handler)
  {
    std::error_code ec;
    auto content_length = get<rfc7230::content_length_t>(r, ec);

    if (ec) {
      asio::post(
        s.get_executor(),
        [handler, ec]()
        {
          handler(ec);
        }
      );
      return;
    }

    if (content_length) {
      async_read_content(s, i, c, *content_length, handler);
      return;
    }

    // we assume the request does not include a payload.
    //
    asio::post(
      s.get_executor(),
      [handler]
      {
        handler({});
      }
    );
  }

  void
  read_content(common::io::stream_t& s,
               asio::streambuf& i,
               asio::streambuf& c,
               response_t const& r)
  {
    std::error_code ec;
    read_content(s, i, c, r, ec);

    if (ec) {
      throw std::system_error{ec};
    }
  }

  void
  read_content(common::io::stream_t& s,
               asio::streambuf& i,
               asio::streambuf& c,
               response_t const& r,
               std::error_code& ec)
  {
    // fixme: support transfer encoding.
    //

    auto content_length = get<rfc7230::content_length_t>(r, ec);

    if (ec) {
      return;
    }

    if (content_length) {
      read_content(s, i, c, *content_length, ec);
      return;
    }

    // fixme: read until eof.
    //
    // fixme: return error until eof is implemented.
    //
  }

  void
  async_read_content(common::io::stream_t& s,
                     asio::streambuf& i,
                     asio::streambuf& c,
                     response_t const& r,
                     std::function<void(std::error_code)> handler)
  {
    // fixme: support transfer encoding.
    //

    std::error_code ec;
    auto content_length = get<rfc7230::content_length_t>(r, ec);

    if (ec) {
      asio::post(
        s.get_executor(),
        [handler, ec]
        {
          handler(ec);
        }
      );
    }

    if (content_length) {
      async_read_content(s, i, c, *content_length, handler);
      return;
    }

    // fixme: read until eof.
    //
    // fixme: return error until eof is implemented.
    //
  }

} // namespace art::seafire::protocol
