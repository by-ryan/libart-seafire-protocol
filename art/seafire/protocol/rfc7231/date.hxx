#ifndef art__seafire__protocol__rfc7231__date_hxx_
#define art__seafire__protocol__rfc7231__date_hxx_

#include <art/seafire/protocol/date-time.hxx>

#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace art::seafire::protocol::rfc7231
{

  /// fixme: make class
  struct date_t
  {
    using alias_type = std::chrono::system_clock::time_point;

    static constexpr char const name[] = "date";

    static
    std::optional<std::chrono::system_clock::time_point>
    try_parse(std::vector<std::string> const& strings, std::error_code&)
    {
      if (strings.empty()) {
        return std::nullopt;
      }

      return try_parse_http_date(strings.front());
    }

    static
    std::string
    to_string(std::chrono::system_clock::time_point const& time)
    {
      return format_http_date(time);
    }

  };

} // namespace art::seafire::protocol::rfc7231

#endif
