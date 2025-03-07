#ifndef art__seafire__protocol__entity_tag_hxx_
#define art__seafire__protocol__entity_tag_hxx_

#include <optional>
#include <stdexcept>
#include <string>
#include <system_error>

namespace art::seafire::protocol::rfc7232
{

  class entity_tag_t
  {
  public:
    enum class tag_type { strong, weak };

    static constexpr tag_type strong = tag_type::strong;
    static constexpr tag_type weak = tag_type::weak;

    entity_tag_t(std::string tag, tag_type type);

    std::string const&
    tag() const;

    tag_type
    type() const;

    template<typename InputIterator>
    static
    std::optional<entity_tag_t>
    try_parse(InputIterator& it,
              InputIterator const& end,
              std::error_code& ec);

    template<typename InputIterator>
    static
    std::optional<entity_tag_t>
    try_parse(InputIterator&& it,
              InputIterator const& end,
              std::error_code& ec);

  private:
    std::string tag_;
    tag_type type_;
  };

  std::string
  to_string(entity_tag_t const& et);

  bool
  is_strong(entity_tag_t const& et);

  bool
  is_weak(entity_tag_t const& et);

  bool
  operator==(entity_tag_t const& lhs, entity_tag_t const& rhs);

  bool
  operator!=(entity_tag_t const& lhs, entity_tag_t const& rhs);

  bool
  strong_compare(entity_tag_t const& lhs, entity_tag_t const& rhs);

  bool
  weak_compare(entity_tag_t const& lhs, entity_tag_t const& rhs);

  } // namespace art::seafire::protocol::rfc7232

#include <art/seafire/protocol/rfc7232/entity-tag.txx>

#endif
