namespace art::seafire::protocol
{

  template<typename InputIterator>
  std::optional<media_type_t>
  media_type_t::
  try_parse(InputIterator& begin,
            InputIterator const& end,
            std::error_code& ec)
  {
    std::optional<media_type_t> const failure;

    auto skip_whitespace = [&]
    {
      while (begin != end && grammar::is_space(*begin)) {
        ++begin;
      }
    };

    auto try_parse_token = [&]() -> std::optional<std::string>
    {
      if (begin == end)
        return std::nullopt;

      if (!grammar::is_tchar(*begin))
        return std::nullopt;

      std::string token;
      token += *begin;
      ++begin;

      while (begin != end) {
        if (!grammar::is_tchar(*begin))
          break;

        token += *begin;
        ++begin;
      }

      return std::move(token);
    };

    auto try_parse_parameter = [&]() -> std::optional<std::pair<std::string, std::string>>
    {
      if (begin == end || *begin != ';')
        return std::nullopt;

      ++begin; // skips ';'

      skip_whitespace();

      auto name = try_parse_token();

      if (!name || begin == end || *begin != '=')
        return std::nullopt;

      ++begin; // skips '='

      // Quoted-string value?
      if (begin != end && *begin == '"') {
        // fixme: support quoted string values
        //
        return std::nullopt;
      }

      auto value = try_parse_token();

      if (!value)
        return std::nullopt;

      // fixme: normalize parameter name.
      //

      return std::pair<std::string, std::string >{*name, *value};
    };

    auto try_parse_parameters = [&]() -> std::map<std::string, std::string>
    {
      std::map< std::string, std::string > params;

      while (begin != end) {
        auto param = try_parse_parameter();

        if (!param) {
          return params;
        }

        params.insert(*param);

        skip_whitespace();
      }

      return params;
    };

    skip_whitespace();

    auto type = try_parse_token();

    if (!type) {
      return std::nullopt;
    }

    if (begin == end || *begin != '/') {
      return std::nullopt;
    }

    ++begin; // skips '/'

    auto subtype = try_parse_token();

    if (!subtype) {
      return std::nullopt;
    }

    skip_whitespace();

    return {{
      std::move(*type),
      std::move(*subtype),
      try_parse_parameters()
    }};
  }

} // namespace art::seafire::protocol
