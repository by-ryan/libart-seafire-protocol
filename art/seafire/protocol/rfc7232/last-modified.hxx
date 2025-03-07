#ifndef art__seafire__protocol__rc7232__last_modified_hxx_
#define art__seafire__protocol__rc7232__last_modified_hxx_

#include <art/seafire/protocol/date-time.hxx>

#include <chrono>
#include <optional>
#include <string>
#include <system_error>
#include <vector>

namespace art::seafire::protocol::rfc7232
{

  struct last_modified_t
  {
    using alias_type = std::chrono::system_clock::time_point;

    static constexpr const char name[] = "last-modified";

    static std::string
    to_string(std::chrono::system_clock::time_point const& point_in_time)
    {
      return format_http_date(point_in_time);
    }

    static std::optional<std::chrono::system_clock::time_point>
    try_parse(std::vector<std::string> const& strings)
    {
      if (strings.empty())
        return std::nullopt;

      return try_parse_http_date(strings.front());
    }
  };

} // namespace art::seafire::protocol::rfc7232

#endif
