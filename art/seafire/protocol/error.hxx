#ifndef art__seafire__protocol__error_hxx_
#define art__seafire__protocol__error_hxx_

#include <string>
#include <system_error>

namespace art::seafire::protocol
{

  enum class parse_error_t
  {
    incomplete_message = 1,

    // Common.
    bad_version,
    bad_header_field,
    bad_header_value,
    bad_terminator,

    // Request-specific.
    bad_method,
    bad_target,

    // Response-specific.
    bad_status,
    bad_reason

  };

  std::error_category const&
  get_parse_error_category();

  std::error_code
  make_error_code(parse_error_t);

  enum class protocol_error_t
  {
    // indicates an invalid content-length.
    //
    invalid_content_length = 1,

    // indicates a too big request body.
    //
    request_too_large,

    // content-length missing.
    //
    length_required,

    // For now.
    //
    invalid_header_value

  };

  std::error_category const&
  get_protocol_error_category();

  std::error_code
  make_error_code(protocol_error_t);

} // namespace art::seafire::protocol

namespace std
{

  template<>
  struct is_error_code_enum<art::seafire::protocol::parse_error_t>
    : true_type
  {};

  template<>
  struct is_error_code_enum<art::seafire::protocol::protocol_error_t>
    : true_type
  {};

} // namespace std

#endif
