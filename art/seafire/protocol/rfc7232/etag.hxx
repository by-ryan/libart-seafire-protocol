#ifndef art__seafire__protocol__rfc7232__etag_hxx_
#define art__seafire__protocol__rfc7232__etag_hxx_

#include <art/seafire/protocol/rfc7232/entity-tag.hxx>

namespace art::seafire::protocol::rfc7232
{

  struct etag_t {
    using alias_type = entity_tag_t;

    static constexpr char const name[] = "etag";

  };

} // namespace art::seafire::protocol::rcf7232

#endif
