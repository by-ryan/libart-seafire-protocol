#ifndef art__seafire__protocol__status_code_hxx_
#define art__seafire__protocol__status_code_hxx_

#include <art/seafire/protocol/reason.hxx>

#include <string>

namespace art::seafire::protocol
{

  /// Represents an HTTP status code.
  ///
  class status_code_t
  {
  public:
    status_code_t();

    status_code_t(unsigned short code);

    status_code_t(unsigned short code, std::string reason);

    unsigned short
    code() const;

    std::string const&
    reason() const;

    operator unsigned short();

  private:
    unsigned short code_{0};
    std::string reason_;

  };

  bool
  operator==(status_code_t const&, status_code_t const&);

  bool
  operator==(status_code_t const&, unsigned short);

  bool
  operator==(unsigned short, status_code_t const&);

  bool
  operator!=(status_code_t const&, status_code_t const&);

  bool
  operator!=(status_code_t const&, unsigned short);

  bool
  operator!=(unsigned short, status_code_t const&);

  bool
  is_informational(status_code_t const&);

  bool
  is_success(status_code_t const&);

  bool
  is_redirection(status_code_t const&);

  bool
  is_client_error(status_code_t const&);

  bool
  is_server_error(status_code_t const&);

} // namespace art::seafire::protocol

#endif
