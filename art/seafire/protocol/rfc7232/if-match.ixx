namespace art::seafire::protocol::rfc7232
{

  inline
  if_match_t::
  if_match_t(anything_t)
    : value_{anything}
  {}

  inline
  if_match_t::
  if_match_t(std::vector<entity_tag_t> tags)
    : value_{std::move(tags)}
  {}

  inline
  bool
  if_match_t::
  is_anything() const
  {
    return std::holds_alternative<anything_t>(value_);
  }

  inline
  std::vector<entity_tag_t> const&
  if_match_t::
  tags() const
  {
    if (std::holds_alternative<std::vector<entity_tag_t>>(value_))
      return std::get<std::vector<entity_tag_t>>(value_);

    throw std::invalid_argument{"invalid if-match"};
  }

  inline
  std::optional<if_match_t>
  if_match_t::
  try_parse(std::vector<std::string> const& strings,
            std::error_code& ec)
  {
    std::vector<entity_tag_t> tags;

    for (auto const& j : strings) {
      auto it = j.begin();

      while (it != j.end()) {
        grammar::skip_space(it, j.end());

        if (it != j.end() && *it == '*') {
          ++it; // consume '*'

          grammar::skip_space(it, j.end());

          if (it != j.end() || tags.size() > 0) {
            ec = make_error_code(protocol_error_t::invalid_header_value);
            return std::nullopt;
          }

          return anything;
        }

        auto tag = entity_tag_t::try_parse(it, j.end(), ec);

        if (ec)
          return std::nullopt;

        if (!tag) {
          ec = make_error_code(protocol_error_t::invalid_header_value);
          return std::nullopt;
        }

        tags.emplace_back(std::move(*tag));

        grammar::skip_space(it, j.end());

        if (it != j.end()) {
          if (*it != ',') {
            ec = make_error_code(protocol_error_t::invalid_header_value);
            return std::nullopt;
          }

          ++it;
        }
      }
    }

    if (tags.empty())
      return {};

    return tags;
  }

  inline
  std::string
  to_string(if_match_t const& if_match)
  {
    if (if_match.is_anything())
      return "*";

    std::ostringstream str;

    auto it = if_match.tags().begin();

    if (it != if_match.tags().end())
      str << to_string(*it++);

    while (it != if_match.tags().end()) {
      str << ", ";
      str << to_string(*it++);
    }

    return str.str();
  }

} // namespace art::seafire::protocol::rfc7232
