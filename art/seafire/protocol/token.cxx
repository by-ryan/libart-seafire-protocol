#include <art/seafire/protocol/token.hxx>

namespace art::seafire::protocol
{

  /// Construct a new empty token.
  ///
  token_t::
  token_t() = default;

  /// Construct a new token from a string.
  ///
  /// \param str The token string.
  /// \throws std::invalid_argument Thrown if \a str is invalid.
  ///
  token_t::
  token_t(std::string str)
    : str_{
      validate_token(str)
        ? std::move(str)
        : throw std::invalid_argument{"invalid token"}
    }
  {}

  /// Construct a new token from a string.
  ///
  /// \param str The token string.
  /// \throws std::invalid_argument Thrown if \a str is invalid.
  ///
  token_t::
  token_t(char const* str)
    : str_{
      str
      ? (
        validate_token(str)
          ? str
          : throw std::invalid_argument{"invalid token"}
        )
      : throw std::invalid_argument{"invalid token"}
    }
  {}

  bool
  token_t::
  empty() const
  {
    return str().empty();
  }

  std::string const&
  token_t::
  str() const
  {
    return str_;
  }

  bool
  token_t::
  validate_token(std::string const& str)
  {
    // we allow empty tokens for the sake of simplicity.
    //
    if (str.empty())
      return true;

    for (auto const& c : str) {
      if (!grammar::is_tchar(c))
        return false;
    }

    return true;
  }

  std::ostream&
  operator<<(std::ostream& o, token_t const& t)
  {
    return o << t.str();
  }

} // namespace art::seafire::protocol
