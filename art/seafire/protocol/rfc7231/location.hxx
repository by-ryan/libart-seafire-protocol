#ifndef art__seafire__protocol__rc7231__location_hxx_
#define art__seafire__protocol__rc7231__location_hxx_

#include <art/uri/uri.hxx>

#include <string>
#include <system_error>

namespace art::seafire::protocol::rfc7231
{

  struct location_t
  {
    using alias_type = art::uri::uri_t;
  
    static constexpr const char name[] = "location";
  
    static
    std::string
    to_string(art::uri::uri_t const& location)
    {
      return art::uri::to_string(location);
    }
  };

} // namespace art::seafire::protocol::rfc7231

#endif
