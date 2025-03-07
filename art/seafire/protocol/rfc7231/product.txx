namespace art::seafire::protocol::rfc7231
{

  template<typename InputIterator>
  std::optional<product_t>
  try_parse_product(InputIterator& first, InputIterator last)
  {
    auto name = try_parse_token(first, last);

    if (!name) {
      return std::nullopt;
    }

    if (first != last && *first == '/') {
      ++first; // skips '/'
      auto version = try_parse_token(first, last);

      if (!version) {
        return std::nullopt;
      }

      return {{*name, *version}};
    }

    return {{*name}};
  }

  template<typename InputIterator>
  std::optional<product_t>
  try_parse_product(InputIterator& first, InputIterator last, std::error_code& ec)
  {
    ec = {};

    auto name = try_parse_token(first, last, ec);

    if (ec) {
      return std::nullopt;
    }

    if (!name) {
      return std::nullopt;
    }

    if (first != last && *first == '/') {
      ++first; // skips '/'
      auto version = try_parse_token(first, last, ec);

      if (ec) {
        return std::nullopt;
      }

      if (!version) {
        return std::nullopt;
      }

      return {{*name, *version}};
    }

    return {{*name}};
  }


  template<typename InputIterator>
  std::optional<products_t>
  try_parse_products(InputIterator& first, InputIterator last)
  {
    products_t products;

    while (first != last) {
      auto p = try_parse_product(first, last);

      if (!p) {
        return std::nullopt;
      }

      products.emplace_back(std::move(*p));

      while (first != last && grammar::is_space(*first)) {
        ++first; // skips whitespace
      }
    }

    return products;
  }

  template<typename InputIterator>
  std::optional<products_t>
  try_parse_products(InputIterator& first, InputIterator last, std::error_code& ec)
  {
    ec = {};

    products_t products;

    while (first != last) {
      auto p = try_parse_product(first, last, ec);

      if (ec) {
        return std::nullopt;
      }

      if (!p) {
        return std::nullopt;
      }

      products.emplace_back(std::move(*p));

      while (first != last && grammar::is_space(*first)) {
        ++first; // skips whitespace
      }
    }

    return products;
  }

} // namespace art::seafire::protocol::rfc7231
