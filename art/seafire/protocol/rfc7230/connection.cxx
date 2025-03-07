#include <art/seafire/protocol/rfc7230/connection.hxx>

namespace art::seafire::protocol::rfc7230
{

  connection_t::
  connection_t(std::set<token_t> tokens)
    : tokens_{std::move(tokens)}
  {}

  connection_t::
  connection_t(std::initializer_list<token_t> tokens)
    : tokens_{tokens.begin(), tokens.end()}
  {}

  std::set<token_t> const&
  connection_t::
  tokens() const
  {
    return tokens_;
  }

  bool
  connection_t::
  close() const
  {
    return tokens().find("close") != tokens().end();
  }

  bool
  connection_t::
  keep_alive() const
  {
    return tokens().find("keep-alive") != tokens().end();
  }

  bool
  connection_t::
  upgrade() const
  {
    return tokens().find("upgrade") != tokens().end();
  }

  std::optional<connection_t>
  connection_t::
  try_parse(std::vector<std::string> const& strings, std::error_code&)
  {
    std::set<token_t> tokens;

    for (auto const& j : strings) {
      auto begin = j.begin();
      auto end = j.end();

      auto t = try_parse_tokens(begin, end);

      if (!t) {
        return std::nullopt;
      }

      if (begin != end) {
        return std::nullopt;
      }

      for (auto const& k : *t) {
        tokens.emplace(k);
      }
    }

    return std::set<token_t>{tokens.begin(), tokens.end()};
  }

  std::string
  to_string(connection_t const& c)
  {
    std::string joined;

    for (auto const& j : c.tokens()) {
      if (!joined.empty()) {
        joined.append(", ");
      }

      joined.append(j.str());
    }

    return joined;
  }

} // namespace art::seafire::protocol::rfc7230
