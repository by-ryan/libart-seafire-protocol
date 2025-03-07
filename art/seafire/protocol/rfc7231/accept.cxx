#include <art/seafire/protocol/rfc7231/accept.hxx>

namespace art::seafire::protocol::rfc7231
{

  std::optional<media_range_t>
  accept_t::
  try_parse(std::vector<std::string> const& strings, std::error_code& ec)
  {
    if (strings.empty())
      return std::nullopt;

    return media_range_t::try_parse(strings, ec);
  }

} // namespace art::seafire::protocol::rfc7231
