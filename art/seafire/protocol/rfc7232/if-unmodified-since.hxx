#ifndef art__seafire__protocol__rfc7232__if_unmodified_since_hxx_
#define art__seafire__protocol__rfc7232__if_unmodified_since_hxx_

#include <art/seafire/protocol/rfc7232/entity-tag.hxx>

#include <optional>
#include <string>
#include <system_error>
#include <vector>

namespace art::seafire::protocol::rfc7232
{

  struct if_unmodified_since_t
  {
    using alias_type = std::chrono::system_clock::time_point;

    static constexpr const char name[] = "if-unmodified-since";

    static std::string
    to_string(std::chrono::system_clock::time_point const& point_in_time)
    {
      return format_http_date(point_in_time);
    }

    static std::optional<std::chrono::system_clock::time_point>
    try_parse(std::vector<std::string> const& strings, std::error_code& ec)
    {
      if (strings.empty())
        return {};

      return try_parse_http_date(strings.front());
    }
  };

} // namespace art::seafire::protocol::rfc7232

#endif
