#include <art/seafire/protocol/rfc7231/product.hxx>

namespace art::seafire::protocol::rfc7231
{

  product_t::
  product_t(token_t name)
    : name_{std::move(name)}
  {}

  product_t::
  product_t(token_t name, token_t version)
    : name_{std::move(name)},
      version_{std::move(version)}
  {}

  token_t const&
  product_t::
  name() const
  {
    return name_;
  }

  std::optional<token_t> const&
  product_t::
  version() const
  {
    return version_;
  }

  void
  to_stream(std::ostream& o, product_t const& p)
  {
    if (p.name().empty())
      return;

    o << p.name();

    if (p.version() && !p.version()->empty())
      o << "/" << *p.version();
  }

  std::string
  to_string(product_t const& p)
  {
    std::ostringstream str_stream;
    to_stream(str_stream, p);
    return str_stream.str();
  }

  void
  to_stream(std::ostream& o, products_t const& products)
  {
    for (auto const& j : products) {
      to_stream(o, j);
      o << " ";
    }
  }

  std::string
  to_string(products_t const& products)
  {
    std::ostringstream str_stream;
    to_stream(str_stream, products);
    return str_stream.str();
  }

  std::optional<product_t>
  try_parse_product(std::string const& str)
  {
    auto begin = str.begin();
    return try_parse_product(begin, str.end());
  }

  std::optional<product_t>
  try_parse_product(std::string const& str, std::error_code& ec)
  {
    auto begin = str.begin();
    return try_parse_product(begin, str.end(), ec);
  }

  std::optional<products_t>
  try_parse_products(std::string const& str)
  {
    auto begin = str.begin();
    return try_parse_products(begin, str.end());
  }

  std::optional<products_t>
  try_parse_products(std::string const& str, std::error_code& ec)
  {
    auto begin = str.begin();
    return try_parse_products(begin, str.end(), ec);
  }

} // namespace art::seafire::protocol::rfc7231
