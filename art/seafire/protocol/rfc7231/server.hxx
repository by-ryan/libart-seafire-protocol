#ifndef art__seafire__protocol__rfc7231__server_hxx_
#define art__seafire__protocol__rfc7231__server_hxx_

#include <art/seafire/protocol/rfc7231/product.hxx>

#include <optional>
#include <string>

namespace art::seafire::protocol::rfc7231
{

  struct server_t
  {
    using alias_type = products_t;

    static constexpr const char* name = "server";

    static
    std::optional<products_t>
    try_parse(std::vector<std::string> const& strings)
    {
      if (auto it = strings.rbegin(); it != strings.rend())
        return try_parse_products(*it);

      return {};
    }

    static
    std::optional<products_t>
    try_parse(std::vector<std::string> const& strings, std::error_code& ec)
    {
      if (auto it = strings.rbegin(); it != strings.rend())
        return try_parse_products(*it, ec);

      return {};
    }

  };

} // namespace art::seafire::protocol::rfc7231

#endif
