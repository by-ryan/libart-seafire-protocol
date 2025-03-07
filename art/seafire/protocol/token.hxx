#ifndef art__seafire__protocol__token_hxx_
#define art__seafire__protocol__token_hxx_

#include <art/seafire/protocol/grammar.hxx>

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace art::seafire::protocol
{

  class token_t
  {
  public:
    token_t();

    token_t(std::string);

    token_t(char const*);

    bool
    empty() const;

    std::string const&
    str() const;

    auto
    operator<=>(token_t const&) const = default;

    static
    bool
    validate_token(std::string const&);

  private:
    std::string str_;

  };

  std::ostream&
  operator<<(std::ostream&, token_t const&);

  /// Vector of tokens.
  ///
  using tokens_t = std::vector<token_t>;

  /// Attempt to parse a token.
  ///
  template<typename Iterator>
  std::optional<token_t>
  try_parse_token(Iterator& begin, Iterator end)
  {
    std::string token;

    while (begin != end && grammar::is_space(*begin)) {
      ++begin;
    }

    while (begin != end && grammar::is_tchar(*begin)) {
      token += *begin++;
    }

    if (token.empty()) {
      return std::nullopt;
    }

    return token;
  }

  template<typename Iterator>
  std::optional<token_t>
  try_parse_token(Iterator& begin, Iterator end, std::error_code& ec)
  {
    ec = {};

    std::string token;

    while (begin != end && grammar::is_space(*begin)) {
      ++begin;
    }

    while (begin != end && grammar::is_tchar(*begin)) {
      token += *begin++;
    }

    if (token.empty()) {
      return std::nullopt;
    }

    return token;
  }

  /// Attempt to parse tokens.
  ///
  template<typename Iterator>
  std::optional<tokens_t>
  try_parse_tokens(Iterator& begin, Iterator end)
  {
    tokens_t tokens;

    while (begin != end) {
      while (begin != end && grammar::is_space(*begin)) {
        ++begin;
      }

      auto token = try_parse_token(begin, end);

      if (!token) {
        return std::nullopt;
      }

      tokens.emplace_back(std::move(*token));

      while (begin != end && grammar::is_space(*begin)) {
        ++begin;
      }

      if (begin == end || *begin != ',') {
        break;
      }

      ++begin; // skips ','
    }

    return tokens;
  }

  /// Attempt to parse tokens.
  ///
  template<typename Iterator>
  std::optional<tokens_t>
  try_parse_tokens(Iterator& begin, Iterator end, std::error_code& ec)
  {
    tokens_t tokens;

    while (begin != end) {
      while (begin != end && grammar::is_space(*begin)) {
        ++begin;
      }

      auto token = try_parse_token(begin, end, ec);

      if (ec) {
        return std::nullopt;
      }

      if (!token) {
        return std::nullopt;
      }

      tokens.emplace_back(std::move(*token));

      while (begin != end && grammar::is_space(*begin)) {
        ++begin;
      }

      if (begin == end || *begin != ',') {
        break;
      }

      ++begin; // skips ','
    }

    return tokens;
  }

} // namespace art::seafire::protocol

#endif
