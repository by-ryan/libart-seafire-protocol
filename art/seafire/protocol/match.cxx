#include <art/seafire/protocol/match.hxx>

namespace art::seafire::protocol
{

  match_request_t::
  match_request_t(request_t& m)
    : message_{m}
  {}

  std::pair<char const*, bool>
  match_request_t::
  operator()(char const* begin, char const* end, std::error_code& ec)
  {
    if (begin == end)
      return std::make_pair(begin, false);

    parser_type p;

    auto const last = p.parse(begin, end, ec);

    if (ec == parse_error_t::incomplete_message) {
      // reset ec, so that the match will be attempted again.
      //
      ec = std::error_code{};
      return std::make_pair(begin, false);
    }

    if (ec)
      return std::make_pair(begin, true);

    extract_message(p, message_);
    return std::make_pair(last, true);
  }

  match_response_t::
  match_response_t(response_t& m)
    : message_{m}
  {}

  std::pair<char const*, bool>
  match_response_t::
  operator()(char const* begin, char const* end, std::error_code& ec)
  {
    if (begin == end)
      return std::make_pair(begin, false);

    parser_type p;

    auto const last = p.parse(begin, end, ec);

    if (ec == parse_error_t::incomplete_message) {
      // reset ec, so that the match will be attempted again.
      //
      ec = std::error_code{};
      return std::make_pair(begin, false);
    }

    if (ec)
      return std::make_pair(begin, true);

    extract_message(p, message_);
    return std::make_pair(last, true);
  }

} // namespace art::seafire::protocol
