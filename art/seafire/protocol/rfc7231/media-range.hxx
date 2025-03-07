#ifndef art__seafire__protocol__rc7231__media_range_hxx_
#define art__seafire__protocol__rc7231__media_range_hxx_

#include <art/seafire/protocol/media-type.hxx>

#include <algorithm>
#include <system_error>
#include <vector>

namespace art::seafire::protocol::rfc7231
{

  class media_range_t {
  public:
    using const_iterator = typename std::vector<media_type_t>::const_iterator;

    media_range_t();

    media_range_t(media_type_t type);

    media_range_t(std::vector<media_type_t> types);

    const_iterator
    begin() const;

    const_iterator
    cbegin() const;

    const_iterator
    end() const;

    const_iterator
    cend() const;

    std::vector<media_type_t> const&
    get() const;

    template<typename InputIterator>
    static
    std::optional<media_range_t>
    try_parse(InputIterator& begin,
              InputIterator const& end,
              std::error_code& ec);

    static
    std::optional<media_range_t>
    try_parse(std::vector<std::string> const& strings, std::error_code& ec);

  private:
    void
    sort_internals();

    std::vector<media_type_t> types_;
  };

} // namespace art::seafire::protocol::rfc7231

#include <art/seafire/protocol/rfc7231/media-range.txx>

#endif
