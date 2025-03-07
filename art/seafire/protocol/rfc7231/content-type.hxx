#ifndef art__seafire__protocol__rfc7231__content_type_hxx_
#define art__seafire__protocol__rfc7231__content_type_hxx_

#include <art/seafire/protocol/media-type.hxx>

#include <optional>
#include <string>
#include <vector>

namespace art::seafire::protocol::rfc7231
{

  // fixme: make class
  struct content_type_t
  {
    using alias_type = media_type_t;

    static constexpr char const name[] = "content-type";

    static
    std::optional<media_type_t>
    try_parse(std::vector<std::string> const&, std::error_code&);

  };

} // namespace art::seafire::protocol::rfc7231

#endif
