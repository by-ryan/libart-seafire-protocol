#ifndef art__seafire__protocol__protocol_version_hxx_
#define art__seafire__protocol__protocol_version_hxx_

#include <art/seafire/common/io/buffer.hxx>

#include <asio.hpp>

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace art::seafire::protocol
{

  /// Represents an HTTP version.
  ///
  struct version_t
  {
    /// Construct a new protocol version.
    ///
    constexpr
    version_t() noexcept
      : major{0}, minor{0}
    {}

    /// Construct a new protocol version.
    ///
    /// \param major The major version number.
    /// \param minor The minor version number.
    ///
    constexpr
    version_t(std::uint16_t major, std::uint16_t minor) noexcept
      : major{major}, minor{minor}
    {}

    bool
    operator==(version_t const&) const noexcept;

    bool
    operator!=(version_t const&) const noexcept;

    std::uint16_t major;
    std::uint16_t minor;

  };

  inline constexpr version_t const http_1_0{1, 0};

  inline constexpr version_t const http_1_1{1, 1};

  std::ostream&
  to_stream(std::ostream&, version_t const&);

  std::string
  to_string(version_t const&);

  std::ostream&
  operator<<(std::ostream&, version_t const&);

  void
  to_buffers(common::io::const_buffers_t&, version_t const&);

} // namespace art::seafire::protocol

#endif
