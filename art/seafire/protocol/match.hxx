#ifndef art__seafire__protocol__match_hxx_
#define art__seafire__protocol__match_hxx_

#include <art/seafire/protocol/basic-parser.hxx>
#include <art/seafire/protocol/error.hxx>
#include <art/seafire/protocol/request.hxx>
#include <art/seafire/protocol/response.hxx>

#include <system_error>
#include <utility>

namespace art::seafire::protocol
{

  /// Implements an input match condition for matching a request.
  ///
  class match_request_t
  {
  public:
    using parser_type = basic_request_parser_t<char const*>;

    explicit
    match_request_t(request_t& m);

    std::pair<char const*, bool>
    operator()(char const*, char const*, std::error_code&);

  private:
    request_t& message_;

  };

  /// Implements an input match condition for matching a response.
  ///
  class match_response_t
  {
  public:
    using parser_type = basic_response_parser_t<char const*>;

    explicit
    match_response_t(response_t& m);

    std::pair<char const*, bool>
    operator()(char const*, char const*, std::error_code&);

  private:
    response_t& message_;

  };

} // namespace art::seafire::protocol

#endif
