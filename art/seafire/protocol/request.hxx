#ifndef art__seafire__protocol__request_hxx_
#define art__seafire__protocol__request_hxx_

#include <art/seafire/protocol/message.hxx>

#include <art/seafire/common/io/buffer.hxx>

#include <art/uri/uri.hxx>

#include <ostream>
#include <string>
#include <vector>

namespace art::seafire::protocol
{

  class request_t
    : public message_t
  {
  public:
    request_t();

    request_t(std::string, std::string, version_t);

    std::string const&
    method() const;

    void
    set_method(std::string);

    std::string const&
    target() const;

    void
    set_target(std::string);

    art::uri::uri_t const&
    target_uri() const;

    void
    set_target_uri(art::uri::uri_t);

  private:
    std::string method_;
    std::string target_;
    art::uri::uri_t target_uri_;
    std::string query_;

  };

  void
  to_buffers(common::io::const_buffers_t&, request_t const&);

  common::io::const_buffers_t
  to_buffers(request_t const&);

  std::ostream&
  operator<<(std::ostream&, request_t const&);

} // namespace art::seafire::protocol

#endif
