namespace art::seafire::protocol::rfc7232
{

  template<typename InputIterator>
  std::optional<entity_tag_t>
  entity_tag_t::
  try_parse(InputIterator& it,
            InputIterator const& end,
            std::error_code& ec)
  {
    bool weak = false;

    if (it == end)
      return {};

    if (*it == 'W') {
      ++it; // consume 'W'

      if (it == end || *it != '/')
        return {};

      ++it; // consume '/'

      weak = true;
    }

    if (it == end || *it != '"')
      return {};

    ++it; // consume '"'

    std::string opaque;

    while (it != end && *it != '"') // TODO: Validate *it
      opaque += *it++;

    if (it == end || *it != '"')
      return {};

    ++it; // consume '"'

    return entity_tag_t{opaque, weak ? entity_tag_t::weak : entity_tag_t::strong};
  }

  template<typename InputIterator>
  std::optional<entity_tag_t>
  entity_tag_t::
  try_parse(InputIterator&& it,
            InputIterator const& end,
            std::error_code& ec)
  {
    return try_parse(it, end, ec);
  }

} // namespace art::seafire::protocol::rfc7232
