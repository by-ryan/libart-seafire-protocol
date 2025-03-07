#ifndef art__seafire__protocol__rfc7232__if_match_hxx_
#define art__seafire__protocol__rfc7232__if_match_hxx_

#include <art/seafire/protocol/error.hxx>
#include <art/seafire/protocol/grammar.hxx>
#include <art/seafire/protocol/rfc7232/entity-tag.hxx>

#include <optional>
#include <sstream>
#include <string>
#include <system_error>
#include <variant>
#include <vector>

namespace art::seafire::protocol::rfc7232
{

  class if_match_t
  {
  public:
    static constexpr char const name[] = "if-match";

    struct anything_t {};

    static constexpr anything_t anything{};

    if_match_t(anything_t);

    if_match_t(std::vector<entity_tag_t>);

    bool
    is_anything() const;

    std::vector<entity_tag_t> const&
    tags() const;

    static
    std::optional<if_match_t>
    try_parse(std::vector<std::string> const&,
              std::error_code&);

  private:
    std::variant<
      anything_t, std::vector<entity_tag_t>
    > value_;
  };

  std::string
  to_string(if_match_t const&);

} // namespace art::seafire::protocol::rfc7232

#include <art/seafire/protocol/rfc7232/if-match.ixx>

#endif
