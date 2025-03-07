#ifndef art__seafire__protocol__rfc7230__connection_hxx_
#define art__seafire__protocol__rfc7230__connection_hxx_

#include <art/seafire/protocol/token.hxx>

#include <initializer_list>
#include <set>
#include <string>
#include <system_error>

namespace art::seafire::protocol::rfc7230
{

  /// Represents the HTTP `connection` header.
  ///
  class connection_t
  {
  public:
    static constexpr char const name[] = "connection";

    connection_t(std::set<token_t>);

    connection_t(std::initializer_list<token_t>);

    std::set<token_t> const&
    tokens() const;

    bool
    close() const;

    bool
    keep_alive() const;

    bool
    upgrade() const;

    static
    std::optional<connection_t>
    try_parse(std::vector<std::string> const&, std::error_code&);

  private:
    std::set<token_t> tokens_;

  };

  std::string
  to_string(connection_t const&);

} // namespace art::seafire::protocol::rfc7230

#endif
