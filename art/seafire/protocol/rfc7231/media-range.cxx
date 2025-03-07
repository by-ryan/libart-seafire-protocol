#include <art/seafire/protocol/rfc7231/media-range.hxx>

namespace art::seafire::protocol::rfc7231
{

  media_range_t::
  media_range_t()
  {}

  media_range_t::
  media_range_t(media_type_t type)
    : types_{std::move(type)}
  {}

  media_range_t::
  media_range_t(std::vector<media_type_t> types)
    : types_{std::move(types)}
  {
    sort_internals();
  }

  media_range_t::const_iterator
  media_range_t::
  begin() const
  {
    return get().begin();
  }

  media_range_t::const_iterator
  media_range_t::
  cbegin() const
  {
    return get().cbegin();
  }

  media_range_t::const_iterator
  media_range_t::
  end() const
  {
    return get().end();
  }

  media_range_t::const_iterator
  media_range_t::
  cend() const
  {
    return get().cend();
  }

  std::vector<media_type_t> const&
  media_range_t::
  get() const
  {
    return types_;
  }

  std::optional<media_range_t>
  media_range_t::
  try_parse(std::vector<std::string> const& strings, std::error_code& ec)
  {
    if (auto it = strings.rbegin(); it != strings.rend()) {
      auto begin = it->begin();
      return try_parse(begin, it->end(), ec);
    }

    return std::nullopt;
  }

  void
  media_range_t::
  sort_internals()
  {
    struct {
      int
      specificity(media_type_t const& type)
      {
        if (type.type() == "*")
          return 0;

        if (type.subtype() == "*")
          return 1;

        if (type.params().size() < 1)
          return 2;

        return 3;
      }

      bool
      operator()(media_type_t const& a, media_type_t const& b)
      {
        auto const sa = specificity(a);
        auto const sb = specificity(b);

        if (sa == sb) {
          if (a.type() < b.type())
            return true;

          if (a.subtype() < b.subtype())
            return true;

          return false;
        }

        return sb < sa;
      }
    } precedence;

    std::sort(types_.begin(), types_.end(), precedence);
  }

} // namespace art::seafire::protocol::rfc7231
