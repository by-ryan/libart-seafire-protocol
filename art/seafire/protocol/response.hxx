#ifndef art__seafire__protocol__response_hxx_
#define art__seafire__protocol__response_hxx_

#include <art/seafire/protocol/message.hxx>
#include <art/seafire/protocol/status-code.hxx>

#include <art/seafire/common/io/buffer.hxx>

#include <string>
#include <vector>

namespace art::seafire::protocol
{

  /// Represents an HTTP/1.1 response message.
  ///
  class response_t
    : public message_t
  {
  public:
    response_t();

    response_t(version_t, status_code_t);

    status_code_t const&
    status() const;

    void
    set_status(status_code_t status);

  private:
    status_code_t status_;

  };

  void
  to_buffers(common::io::const_buffers_t&, response_t const&);

  common::io::const_buffers_t
  to_buffers(response_t const&);

} // namespace art::seafire::protocol

#endif
