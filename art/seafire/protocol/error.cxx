#include <art/seafire/protocol/error.hxx>

namespace art::seafire::protocol
{

  std::error_category const&
  get_parse_error_category()
  {
    class category_t
      : public std::error_category
    {
    public:
      char const*
      name() const noexcept override
      {
        return "code.seafire.parser";
      }

      std::string
      message(int ec) const override
      {
        switch (static_cast<parse_error_t>(ec)) {
          case parse_error_t::incomplete_message: return "incomplete message";
          case parse_error_t::bad_version: return "bad version";
          case parse_error_t::bad_header_field: return "bad header field";
          case parse_error_t::bad_header_value: return "bad header value";
          case parse_error_t::bad_terminator: return "bad terminator";
          case parse_error_t::bad_method: return "bad method";
          case parse_error_t::bad_target: return "bad target";
          case parse_error_t::bad_status: return "bad status";
          case parse_error_t::bad_reason: return "bad reason";
        }

        return "code.seafire.parser error";
      }
    };

    static category_t const category;

    return category;
  }

  std::error_code
  make_error_code(parse_error_t error)
  {
    return {static_cast<int>(error), get_parse_error_category()};
  }

  std::error_category const&
  get_protocol_error_category()
  {
    class category_t
      : public std::error_category
    {
    public:
      char const*
      name() const noexcept override
      {
        return "code.seafire.protocol";
      }

      std::string
      message(int ec) const override
      {
        switch (static_cast<protocol_error_t>(ec)) {
          case protocol_error_t::invalid_content_length: return "invalid content length";
          case protocol_error_t::request_too_large: return "request too large";
          case protocol_error_t::length_required: return "length required";
          case protocol_error_t::invalid_header_value: return "invalid header value";
        }

        return "code.seafire.protocol error";
      }

    };

    static category_t const category;

    return category;
  }

  std::error_code
  make_error_code(protocol_error_t error)
  {
    return {static_cast<int>(error), get_protocol_error_category()};
  }

} // namespace art::seafire::protocol
