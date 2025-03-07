#ifndef art__seafire__protocol__rfc7232__if_none_match_hxx_
#define art__seafire__protocol__rfc7232__if_none_match_hxx_

#include <art/seafire/protocol/rfc7232/entity-tag.hxx>

#include <optional>
#include <system_error>

namespace art::seafire::protocol::rfc7232
{

  struct if_none_match_t
  {
    static constexpr char const name[] = "if-none-match";

    static std::optional<if_none_match_t>
    try_parse(std::vector<std::string> const& strings, std::error_code& ec)
    {
      // FIXME implement.
      return {};
    }
  };

  inline
  std::string
  to_string(if_none_match_t const& if_none_match)
  {
    // FIXME implement.
    return {};
  }

} // namespace art::seafire::protocol::rfc7232

#endif
