#ifndef art__seafire__protocol__rfc7230__host_hxx_
#define art__seafire__protocol__rfc7230__host_hxx_

#include <optional>
#include <string>
#include <system_error>
#include <vector>

namespace art::seafire::protocol::rfc7230
{

  class host_t
  {
  public:
    static constexpr char const name[] = "host";

    explicit
    host_t(std::string);

    host_t(std::string, std::optional<std::string>);

    std::string const&
    hostname() const;

    std::optional<std::string> const&
    port() const;

    static
    std::optional<host_t>
    try_parse(std::vector<std::string> const&, std::error_code&);

  private:
    std::string hostname_;
    std::optional<std::string> port_;

  };

  std::string
  to_string(host_t const&);

} // namespace art::seafire::protocol::rfc7230

#endif
