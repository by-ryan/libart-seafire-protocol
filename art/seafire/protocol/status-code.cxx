#include <art/seafire/protocol/status-code.hxx>

#include <stdexcept>

namespace art::seafire::protocol
{

  status_code_t::
  status_code_t() = default;

  /// Construct a new status code.
  ///
  /// Valid codes are 100 to 999 (inclusive).
  ///
  /// The reason string will be set if the status code is standard.
  ///
  /// \throws std::invalid_argument Thrown if \a code is invalid.
  ///
  status_code_t::
  status_code_t(unsigned short code)
    : code_{code}, reason_{get_reason(code)}
  {
    if (code < 100 || 999 < code) {
      throw std::invalid_argument{"invalid status code"};
    }
  }

  /// Construct a new status code with a custom reason.
  ///
  /// Valid codes are 100 to 999 (inclusive).
  ///
  /// \throws std::invalid_argument Thrown if \a code is invalid.
  ///
  status_code_t::
  status_code_t(unsigned short code, std::string reason)
    : code_{ code }, reason_{ std::move(reason) }
  {
    if (code < 100 || 999 < code) {
      throw std::invalid_argument{"invalid status code"};
    }
  }

  /// Access the code of this status code.
  ///
  unsigned short
  status_code_t::
  code() const
  {
    return code_;
  }

  /// Access the reason string of this status code.
  ///
  std::string const&
  status_code_t::
  reason() const
  {
    return reason_;
  }

  /// Convert this status code to an unsigned short value.
  ///
  status_code_t::
  operator unsigned short()
  {
    return code_;
  }

  /// Compare two status codes for equality.
  ///
  bool
  operator==(status_code_t const& lhs, status_code_t const& rhs)
  {
    return lhs.code() == rhs.code();
  }

  /// Compare two status codes for equality.
  ///
  bool
  operator==(status_code_t const& lhs, unsigned short rhs)
  {
    return lhs.code() == rhs;
  }

  /// Compare two status codes for equality.
  ///
  bool
  operator==(unsigned short lhs, status_code_t const& rhs)
  {
    return lhs == rhs.code();
  }

  /// Compare two status codes for inequality.
  ///
  bool
  operator!=(status_code_t const& lhs, status_code_t const& rhs)
  {
    return !(lhs == rhs);
  }

  /// Compare two status codes for inequality.
  ///
  bool
  operator!=(status_code_t const& lhs, unsigned short rhs)
  {
    return !(lhs == rhs);
  }

  /// Compare two status codes for inequality.
  ///
  bool
  operator!=(unsigned short lhs, status_code_t const& rhs)
  {
    return !(lhs == rhs);
  }

  /// Check if the given status code, \a sc, is informational.
  ///
  bool
  is_informational(status_code_t const& sc)
  {
    return (sc.code() / 100) == 1;
  }

  /// Check if the given status code, \a sc, indicates success.
  ///
  bool
  is_success(status_code_t const& sc)
  {
    return (sc.code() / 100) == 2;
  }

  /// Check if the given status code, \a sc, is a redirection.
  ///
  bool
  is_redirection(status_code_t const& sc)
  {
    return (sc.code() / 100) == 3;
  }

  /// Check if the given status code, \a sc, indicates a client error.
  ///
  bool
  is_client_error(status_code_t const& sc)
  {
    return (sc.code() / 100) == 4;
  }

  /// Check if the given status code, \a sc, indicates a server error.
  ///
  bool
  is_server_error(status_code_t const& sc)
  {
    return (sc.code() / 100) == 5;
  }

} // namespace art::seafire::protocol
