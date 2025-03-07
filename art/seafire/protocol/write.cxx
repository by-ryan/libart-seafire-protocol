#include <art/seafire/protocol/write.hxx>

namespace art::seafire::protocol
{

  void
  write(common::io::stream_t& s,
        request_t const& r)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);
    s.write(payload);
  }

  void
  write(common::io::stream_t& s,
        request_t const& r,
        std::error_code& ec)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);
    s.write(payload, ec);
  }

  void
  write(common::io::stream_t& s,
        request_t const& r,
        common::io::const_buffers_t const& content)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);

    for (auto const& j : content) {
      payload.emplace_back(j);
    }

    s.write(payload);
  }

  void
  write(common::io::stream_t& s,
        request_t const& r,
        common::io::const_buffers_t const& content,
        std::error_code& ec)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);

    for (auto const& j : content) {
      payload.emplace_back(j);
    }

    s.write(payload, ec);
  }

  void
  async_write(common::io::stream_t& s,
              request_t const& r,
              std::function<void(std::error_code)> handler)
  {
    auto bound = [handler](std::error_code const& ec, std::size_t)
    {
      handler(ec);
    };

    s.async_write(to_buffers(r), bound);
  }

  void
  async_write(common::io::stream_t& s,
              request_t const& r,
              common::io::const_buffers_t const& content,
              std::function<void(std::error_code)> handler)
  {
    auto bound = [handler](std::error_code const& ec, std::size_t)
    {
      handler(ec);
    };

    common::io::const_buffers_t payload;
    to_buffers(payload, r);

    for (auto const& j : content) {
      payload.emplace_back(j);
    }

    s.async_write(payload, bound);
  }

  void
  write(common::io::stream_t& s,
        response_t const& r)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);
    s.write(payload);
  }

  void
  write(common::io::stream_t& s,
        response_t const& r,
        std::error_code& ec)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);
    s.write(payload, ec);
  }

  void
  write(common::io::stream_t& s,
        response_t const& r,
        common::io::const_buffers_t const& content)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);

    for (auto const& j : content) {
      payload.emplace_back(j);
    }

    s.write(payload);
  }

  void
  write(common::io::stream_t& s,
        response_t const& r,
        common::io::const_buffers_t const& content,
        std::error_code& ec)
  {
    common::io::const_buffers_t payload;
    to_buffers(payload, r);

    for (auto const& j : content) {
      payload.emplace_back(j);
    }

    s.write(payload, ec);
  }

  void
  async_write(common::io::stream_t& s,
              response_t const& r,
              std::function<void(std::error_code)> handler)
  {
    auto bound = [handler](std::error_code const& ec, std::size_t)
    {
      handler(ec);
    };

    s.async_write(to_buffers(r), bound);
  }

  void
  async_write(common::io::stream_t& s,
              response_t const& r,
              common::io::const_buffers_t const& content,
              std::function<void(std::error_code)> handler)
  {
    auto bound = [handler](std::error_code const& ec, std::size_t)
    {
      handler(ec);
    };

    common::io::const_buffers_t payload;
    to_buffers(payload, r);

    for (auto const& j : content) {
      payload.emplace_back(j);
    }

    s.async_write(payload, bound);
  }

} // namespace art::seafire::protocol
