#include <art/seafire/protocol/request.hxx>

#include <asio.hpp>

namespace art::seafire::protocol
{

  /// Construct a new request message.
  ///
  request_t::
  request_t()
  {}

  /// Construct a new request message.
  ///
  /// \param method The method of the request message.
  /// \param target The target of the request message.
  /// \param version The version of the request message.
  ///
  request_t::
  request_t(std::string method,
          std::string target,
          version_t version)
  {
    set_method(std::move(method));
    set_target(std::move(target));
    set_version(version);
  }

  /// Access the method of the request message.
  ///
  std::string const&
  request_t::
  method() const
  {
    return method_;
  }

  /// Set the method of the request message.
  ///
  void
  request_t::
  set_method(std::string method)
  {
    method_ = std::move(method);
  }

  /// Access the target of the request message.
  ///
  std::string const&
  request_t::
  target() const
  {
    return target_;
  }

  /// Set the target of the request message.
  ///
  void
  request_t::
  set_target(std::string target)
  {
    target_ = std::move(target);
  }

  /// Access the target of the request as a URI.
  ///
  art::uri::uri_t const&
  request_t::
  target_uri() const
  {
    return target_uri_;
  }

  /// Set the target URI of the request message.
  ///
  void
  request_t::
  set_target_uri(art::uri::uri_t target_uri)
  {
    target_uri_ = std::move(target_uri);
  }

  /// Convert an HTTP request message to byte buffers.
  ///
  /// The buffers are invalidated when the request message is destroyed
  /// or any of its properties are modified.
  ///
  /// The buffers are added to the \a buffers vector.
  ///
  /// \relatesalso request_t
  ///
  void
  to_buffers(common::io::const_buffers_t& buffers, request_t const& r)
  {
    static char const colon_space[]{ ':', ' ' };
    static char const crlf[]{ '\r', '\n' };
    static char const space[]{ ' ' };

    using common::io::buffer;

    buffers.emplace_back(buffer(r.method()));
    buffers.emplace_back(buffer(space));
    buffers.emplace_back(buffer(r.target()));
    buffers.emplace_back(buffer(space));

    to_buffers(buffers, r.version());
    buffers.emplace_back(buffer(crlf));

    for (auto const& header : r.headers()) {
      buffers.emplace_back(buffer(header.first));
      buffers.emplace_back(buffer(colon_space));
      buffers.emplace_back(buffer(header.second));
      buffers.emplace_back(buffer(crlf));
    }

    buffers.emplace_back(buffer(crlf));
  }

  /// Convert an HTTP request message to byte buffers.
  ///
  /// The buffers are invalidated when the request message is destroyed
  /// or any of its properties are modified.
  ///
  /// The buffers are returned as an array of buffers.
  ///
  /// \relatesalso request_t
  ///
  common::io::const_buffers_t
  to_buffers(request_t const& r)
  {
    common::io::const_buffers_t buffers;
    to_buffers(buffers, r);
    return buffers;
  }

  /// Write a request message to an output stream.
  ///
  /// \relatesalso request_t
  ///
  std::ostream&
  operator<<(std::ostream& o, request_t const& r)
  {
    o << r.method() << ' ' << r.target() << ' ' << r.version() << '\n';
    o << static_cast<message_t const&>(r);
    return o;
  }

} // namespace art::seafire::protocol
