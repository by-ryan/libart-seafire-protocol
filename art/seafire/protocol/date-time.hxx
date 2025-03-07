#ifndef art__seafire__protocol__date_time_hxx_
#define art__seafire__protocol__date_time_hxx_

#include <chrono>
#include <optional>
#include <string>

namespace art::seafire::protocol
{

  std::string
  format_http_date(std::chrono::system_clock::time_point const&);

  std::optional<std::chrono::system_clock::time_point>
  try_parse_http_date(std::string const&);

} // namespace art::seafire::protocol

#endif
