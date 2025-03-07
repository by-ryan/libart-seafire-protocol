namespace art::seafire::protocol::rfc7231
{

  template<typename InputIterator>
  std::optional<media_range_t>
  media_range_t::
  try_parse(InputIterator& begin,
            InputIterator const& end,
            std::error_code& ec)
  {
    auto skip_whitespace = [&] {
      while (begin != end && grammar::is_space(*begin))
        ++begin;
    };

    std::vector<media_type_t> types;

    while (begin != end) {
      skip_whitespace();

      auto type = media_type_t::try_parse(begin, end, ec);

      if (ec || !type)
        return std::nullopt;

      types.emplace_back(std::move(*type));

      skip_whitespace();

      if (begin != end && *begin == ',')
        ++begin;
    }

    return types;
  }

} // namespace art::seafire::protocol::rfc7231
