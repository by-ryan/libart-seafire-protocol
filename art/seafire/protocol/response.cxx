#include <art/seafire/protocol/response.hxx>

#include <asio.hpp>

namespace art::seafire::protocol
{

  /// Construct a new response message.
  ///
  response_t::
  response_t() = default;

  /// Construct a new response message.
  ///
  /// \param version The HTTP version of this response message.
  /// \param status  The HTTP status of this response message.
  ///
  response_t::
  response_t(version_t version, status_code_t status)
    : message_t{version},
      status_{status}
  {}

  /// Access the message status.
  ///
  status_code_t const&
  response_t::
  status() const
  {
    return status_;
  }

  /// Set the message status.
  ///
  void
  response_t::
  set_status(status_code_t status)
  {
    status_ = std::move(status);
  }

  /// Convert an HTTP response message to byte buffers.
  ///
  /// The buffers are invalidated when the response message is destroyed
  /// or any of its properties are modified.
  ///
  /// The buffers are added to the \a buffers vector.
  ///
  /// \relatesalso response_t
  ///
  void
  to_buffers(common::io::const_buffers_t& buffers, response_t const& r)
  {
    static char const colon_space[]{':', ' '};
    static char const crlf[]{'\r', '\n'};
    static char const digits[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    static char const space[]{' '};

    using common::io::buffer;

    to_buffers(buffers, r.version());
    buffers.emplace_back(buffer(space));

    auto code = r.status();

    buffers.emplace_back(buffer(&digits[code / 100], 1));
    buffers.emplace_back(buffer(&digits[code % 100 / 10], 1));
    buffers.emplace_back(buffer(&digits[code % 10], 1));
    buffers.emplace_back(buffer(" ", 1));

    buffers.emplace_back(buffer(r.status().reason()));
    buffers.emplace_back(buffer(crlf));

    for (auto const& header : r.headers()) {
      buffers.emplace_back(buffer(header.first));
      buffers.emplace_back(buffer(colon_space));
      buffers.emplace_back(buffer(header.second));
      buffers.emplace_back(buffer(crlf));
    }

    buffers.emplace_back(buffer(crlf));
  }

  /// Convert an HTTP response message to byte buffers.
  ///
  /// The buffers are invalidated when the response message is destroyed
  /// or any of its properties are modified.
  ///
  /// The buffers are returned as an array of buffers.
  ///
  /// \relatesalso response_t
  ///
  common::io::const_buffers_t
  to_buffers(response_t const& r)
  {
    common::io::const_buffers_t buffers;
    to_buffers(buffers, r);
    return buffers;
  }

} // namespace art::seafire::protocol
