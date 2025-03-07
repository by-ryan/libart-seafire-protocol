#ifndef art__seafire__protocol__rfc7231__product_hxx_
#define art__seafire__protocol__rfc7231__product_hxx_

#include <art/seafire/protocol/grammar.hxx>
#include <art/seafire/protocol/token.hxx>

#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace art::seafire::protocol::rfc7231
{

  class product_t {
  public:
    product_t(token_t);

    product_t(token_t, token_t);

    token_t const&
    name() const;

    std::optional<token_t> const&
    version() const;

  private:
    token_t name_;
    std::optional<token_t> version_;

  };

  using products_t = std::vector<product_t>;

  void
  to_stream(std::ostream&, product_t const&);

  std::string
  to_string(product_t const&);

  void
  to_stream(std::ostream&, products_t const&);

  std::string
  to_string(products_t const&);

  template<typename InputIterator>
  std::optional<product_t>
  try_parse_product(InputIterator&, InputIterator);

  template<typename InputIterator>
  std::optional<product_t>
  try_parse_product(InputIterator&, InputIterator, std::error_code& ec);

  std::optional<product_t>
  try_parse_product(std::string const&);

  template<typename InputIterator>
  std::optional<products_t>
  try_parse_products(InputIterator&, InputIterator);
  template<typename InputIterator>

  std::optional<products_t>
  try_parse_products(InputIterator&, InputIterator, std::error_code&);

  std::optional<products_t>
  try_parse_products(std::string const&);

  std::optional<products_t>
  try_parse_products(std::string const&, std::error_code&);

} // namespace art::seafire::protocol::rfc7231

#include <art/seafire/protocol/rfc7231/product.txx>

#endif
