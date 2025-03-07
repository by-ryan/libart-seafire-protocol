#include <art/seafire/protocol/date-time.hxx>

#include <iomanip>
#include <locale>

namespace art::seafire::protocol
{

  std::string
  format_http_date(std::chrono::system_clock::time_point const& time_point)
  {
    static constexpr const char time_format[] = "%a, %d %b %Y %H:%M:%S GMT";

    std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);

    std::stringstream str;
    str.imbue(std::locale{});
    str << std::put_time(std::gmtime(&now_c), time_format);

    return str.str();
  }

  std::optional<std::chrono::system_clock::time_point>
  try_parse_http_date(std::string const& text)
  {
    static constexpr const char time_format[] = "%a, %d %b %Y %H:%M:%S GMT";

    std::tm tm{};

    std::istringstream str{text};
    str.imbue(std::locale{});
    str >> std::get_time(&tm, time_format);

    if (str.fail())
      return {};

    std::time_t time = std::mktime(&tm);

    return std::chrono::system_clock::from_time_t(time);
  }

} // namespace art::seafire::protocol
