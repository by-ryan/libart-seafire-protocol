#include <art/seafire/protocol/rfc7231/content-type.hxx>

namespace art::seafire::protocol::rfc7231
{

  std::optional<media_type_t>
  content_type_t::
  try_parse(std::vector<std::string> const& strings, std::error_code& ec)
  {
    if (auto it = strings.rbegin(); it != strings.rend()) {
      return media_type_t::try_parse(*it, ec);
    }

    return {};
  }

} // namespace art::seafire::protocol::rfc7231
