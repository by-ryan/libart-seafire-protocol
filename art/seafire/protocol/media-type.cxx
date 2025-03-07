#include <art/seafire/protocol/media-type.hxx>

#include <sstream>

namespace art::seafire::protocol
{

  /// Construct a new empty media type.
  ///
  media_type_t::
  media_type_t() = default;

  /// Construct a new media type.
  ///
  media_type_t::
  media_type_t(std::string type, std::string subtype)
    : type_{std::move(type)}, subtype_{std::move(subtype)}
  {}

  /// Construct a new media type.
  ///
  media_type_t::
  media_type_t(std::string type,
               std::string subtype,
               params_t params)
    : type_{std::move(type) },
      subtype_{std::move(subtype)},
      params_{std::move(params)}
  {}

  /// Get the type of this media type.
  ///
  std::string const&
  media_type_t::
  type() const
  {
    return type_;
  }

  /// Get the subtype of this media type.
  ///
  std::string const&
  media_type_t::
  subtype() const
  {
    return subtype_;
  }

  /// Get the parameters of this media type.
  ///
  media_type_t::params_t const&
  media_type_t::
  params() const
  {
    return params_;
  }

  /// Attempt to parse a media type.
  ///
  std::optional< media_type_t>
  media_type_t::
  try_parse(std::string const& str, std::error_code& ec)
  {
    auto begin = str.begin();
    return try_parse(begin, str.end(), ec);
  }

  /// Compare two media types for equality.
  ///
  /// Parameters are ignored.
  ///
  /// \relatesalso media_type_t
  ///
  bool
  operator==(media_type_t const& lhs, media_type_t const& rhs)
  {
    if (lhs.type() != rhs.type()) {
      if ("*" != lhs.type() && "*" != rhs.type()) {
        return false;
      }
    }

    if (lhs.subtype() != rhs.subtype()) {
      if ("*" != lhs.subtype() && "*" != rhs.subtype()) {
        return false;
      }
    }

    return true;
  }

  /// Compare two media types for inequality.
  ///
  /// Parameters are ignored.
  ///
  /// \relatesalso media_type_t
  ///
  bool
  operator!=(media_type_t const& lhs, media_type_t const& rhs)
  {
    return !(lhs == rhs);
  }

  /// Write media type to an output stream.
  ///
  /// \relatesalso media_type_t
  ///
  std::ostream&
  to_stream(std::ostream& o, media_type_t const& m)
  {
    o << m.type() << '/' << m.subtype();
    for (auto const& j : m.params()) {
      o << "; " << j.first << '=' << j.second;
    }
    return o;
  }

  /// Convert a media type to a string.
  ///
  /// \relatesalso media_type_t
  ///
  std::string
  to_string(media_type_t const& m)
  {
    std::stringstream str;
    to_stream(str, m);
    return str.str();
  }

  /// Write a media type to an output stream.
  ///
  /// \relatesalso media_type_t
  ///
  std::ostream&
  operator<<(std::ostream& o, media_type_t const& m)
  {
    return to_stream(o, m);
  }

} // namespace art::seafire::protocol
