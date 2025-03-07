#ifndef art__seafire__protocol__rfc7230__content_length_hxx_
#define art__seafire__protocol__rfc7230__content_length_hxx_

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <system_error>
#include <vector>

namespace art::seafire::protocol::rfc7230
{

  // fixme: make class
  struct content_length_t
  {
    using alias_type = std::uint64_t;

    static constexpr char const name[] = "content-length";

    static
    std::optional<std::size_t>
    try_parse(std::vector<std::string> const&, std::error_code&);

  };

} // namespace art::seafire::protocol::rfc7230

#endif
