#ifndef art__seafire__protocol__rc7231__allow_hxx_
#define art__seafire__protocol__rc7231__allow_hxx_

#include <art/seafire/protocol/token.hxx>

#include <sstream>
#include <string>

namespace art::seafire::protocol::rfc7231
{

  struct allow_t {
    using alias_type = tokens_t;

    static constexpr char const name[] = "allow";

    static
    std::string
    to_string(tokens_t const& tokens)
    {
      std::ostringstream str;

      if (auto it = tokens.begin(); it != tokens.end()) {
        str << *it;

        while (++it != tokens.end())
          str << ", " << *it;
      }

      return str.str();
    }
  };

} // namespace art::seafire::protocol::rfc7231

#endif
