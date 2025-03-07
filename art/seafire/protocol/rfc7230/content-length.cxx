#include <art/seafire/protocol/rfc7230/content-length.hxx>

#include <art/seafire/protocol/error.hxx>

namespace art::seafire::protocol::rfc7230
{

  std::optional<std::size_t>
  content_length_t::
  try_parse(std::vector<std::string> const& strings, std::error_code& ec)
  {
    if (strings.size() == 1) {
      try {
        return std::stoull(strings[0]);
      }
      catch (...) {
        ec = protocol_error_t::invalid_content_length;
        return std::nullopt;
      }
    }
    else if (strings.size() > 1) {
      ec = protocol_error_t::invalid_content_length;
    }

    return std::nullopt;
  }

} // namespace art::seafire::protocol::rfc7230
