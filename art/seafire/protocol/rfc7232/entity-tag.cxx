#include <art/seafire/protocol/rfc7232/entity-tag.hxx>

namespace art::seafire::protocol::rfc7232
{

  entity_tag_t::
  entity_tag_t(std::string tag, tag_type type)
    : tag_{ std::move(tag) }, type_{ type }
  {
    if (auto p = this->tag().find('"'); p != std::string::npos)
      throw std::invalid_argument{ "ETag may not contain \"" };
  }

  std::string const&
  entity_tag_t::
  tag() const
  {
    return tag_;
  }

  entity_tag_t::tag_type
  entity_tag_t::
  type() const
  {
    return type_;
  }

  std::string
  to_string(entity_tag_t const& et)
  {
    if (is_strong(et))
      return "\"" + et.tag() + "\"";

    return "W/\"" + et.tag() + '"';
  }

  bool
  is_strong(entity_tag_t const& et)
  {
    return et.type() == entity_tag_t::strong;
  }

  bool
  is_weak(entity_tag_t const& et)
  {
    return et.type() == entity_tag_t::weak;
  }

  bool
  operator==(entity_tag_t const& lhs, entity_tag_t const& rhs)
  {
    return strong_compare(lhs, rhs);
  }

  bool
  operator!=(entity_tag_t const& lhs, entity_tag_t const& rhs)
  {
    return !(lhs == rhs);
  }

  bool
  strong_compare(entity_tag_t const& lhs, entity_tag_t const& rhs)
  {
    if (is_weak(lhs) || is_weak(rhs))
      return false;

    return lhs.tag() == rhs.tag();
  }

  bool
  weak_compare(entity_tag_t const& lhs, entity_tag_t const& rhs)
  {
    return lhs.tag() == rhs.tag();
  }

} // namespace art::seafire::protocol::rfc7232
