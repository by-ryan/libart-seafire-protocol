#include <art/seafire/protocol/message.hxx>

namespace art::seafire::protocol
{

  /// Construct a new message.
  ///
  message_t::
  message_t() = default;

  /// Construct a new message.
  ///
  message_t::
  message_t(version_t version)
    : version_{version}
  {}

  /// Get the message version.
  ///
  version_t const&
  message_t::
  version() const
  {
    return version_;
  }

  /// Set the message version.
  ///
  void
  message_t::
  set_version(version_t v)
  {
    version_ = std::move(v);
  }

  /// Access the message headers.
  ///
  header_collection_t const&
  message_t::
  headers() const
  {
    return headers_;
  }

  /// Set/replace message header.
  ///
  void
  message_t::
  set_header(std::string name, std::string value)
  {
    headers_.set(std::move(name), std::move(value));
  }

  /// Append message header.
  ///
  void
  message_t::
  append_header(std::string name, std::string value)
  {
    headers_.append(std::move(name), std::move(value));
  }

  /// Erase message header.
  ///
  void
  message_t::
  erase_header(std::string name)
  {
    headers_.erase(name);
  }

  /// Set/replace message headers.
  ///
  void
  message_t::
  set_headers(header_collection_t headers)
  {
    headers_ = std::move(headers);
  }

  /// Write headers to output stream.
  ///
  std::ostream&
  operator<<(std::ostream& o, message_t const& m)
  {
    return o << m.headers();
  }

} // namespace art::seafire::protocol
