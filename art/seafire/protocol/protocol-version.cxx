#include <art/seafire/protocol/protocol-version.hxx>

#include <sstream>

namespace art::seafire::protocol
{

  bool
  version_t::
  operator==(version_t const& other) const noexcept
  {
    return major == other.major && minor == other.minor;
  }

  bool
  version_t::
  operator!=(version_t const& other) const noexcept
  {
    return !(*this == other);
  }

  std::ostream&
  to_stream(std::ostream& o, version_t const& v)
  {
    o << "HTTP/" << v.major << '.' << v.minor;
    return o;
  }

  std::string
  to_string(version_t const& v)
  {
    std::stringstream str;
    to_stream(str, v);
    return str.str();
  }

  std::ostream&
  operator<<(std::ostream& o, version_t const& v)
  {
    return to_stream(o, v);
  }

  void
  to_buffers(common::io::const_buffers_t& buffers, version_t const& v)
  {
    static char constexpr http10[]{'H', 'T', 'T', 'P', '/', '1', '.', '0'};
    static char constexpr http11[]{'H', 'T', 'T', 'P', '/', '1', '.', '1'};

    static char constexpr http[]{'H', 'T', 'T', 'P', '/'};
    static char constexpr digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    static char constexpr dot[]{'.'};

    using common::io::buffer;

    if (v == http_1_0) {
      buffers.emplace_back(buffer(http10));
      return;
    }

    if (v == http_1_1) {
      buffers.emplace_back(buffer(http11));
      return;
    }

    buffers.emplace_back(buffer(http));
    buffers.emplace_back(buffer(&digits[v.major % 10], 1));
    buffers.emplace_back(buffer(dot));
    buffers.emplace_back(buffer(&digits[v.minor % 10], 1));
  }

} // namespace art::seafire::protocol
