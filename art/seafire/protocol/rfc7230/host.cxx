#include <art/seafire/protocol/rfc7230/host.hxx>

#include <art/uri/grammar.hxx>

namespace art::seafire::protocol::rfc7230
{

  host_t::
  host_t(std::string hostname)
    : hostname_{std::move(hostname)}
  {}

  host_t::
  host_t(std::string hostname, std::optional<std::string> port)
    : hostname_{std::move(hostname)}, port_{std::move(port)}
  {}

  std::string const&
  host_t::
  hostname() const
  {
    return hostname_;
  }

  std::optional<std::string> const&
  host_t::
  port() const
  {
    return port_;
  }

  std::optional<host_t>
  host_t::
  try_parse(std::vector<std::string> const& strings, std::error_code&)
  {
    if (auto it = strings.rbegin(); it != strings.rend()) {
      auto first = it->begin();
      auto last = it->end();

      std::string host_part;
      std::optional<std::string> opt_port_part;

      auto try_parse_host = [&](auto init)
      {
        auto c = init;

        while (c != last && art::uri::grammar::is_host(*c)) {
          host_part += *c++;
        }

        return c;
      };

      auto try_parse_port = [&](auto init)
      {
        auto c = init;

        if (c != last && *c == ':') {
          ++c; // skips ':'

          opt_port_part = std::string{};

          while (c != last && art::uri::grammar::is_digit(*c)) {
            *opt_port_part += *c++;
          }

          return c;
        }

        return init;
      };

      first = try_parse_host(first);
      first = try_parse_port(first);

      if (first == last) {
        return {{host_part, opt_port_part}};
      }
    }

    return std::nullopt;
  }

  std::string
  to_string(host_t const& host)
  {
    std::string str{host.hostname()};

    if (host.port())
      str += ':' + *host.port();

    return str;
  }

} // namespace art::seafire::protocol::rfc7230
