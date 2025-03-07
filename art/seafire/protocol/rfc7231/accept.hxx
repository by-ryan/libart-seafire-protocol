#ifndef art__seafire__protocol__rc7231__accept_hxx_
#define art__seafire__protocol__rc7231__accept_hxx_

#include <art/seafire/protocol/rfc7231/media-range.hxx>

#include <optional>
#include <string>
#include <system_error>

namespace art::seafire::protocol::rfc7231
{

  struct accept_t
  {
    using alias_type = media_range_t;

    static constexpr char const name[] = "accept";

    static
    std::optional<media_range_t>
    try_parse(std::vector< std::string > const& strings, std::error_code& ec);

  };

} // namespace art::seafire::protocol::rfc7231

#endif
