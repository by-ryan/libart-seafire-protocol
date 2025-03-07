#ifndef art__seafire__protocol__media_type_hxx_
#define art__seafire__protocol__media_type_hxx_

#include <art/seafire/protocol/grammar.hxx>

#include <map>
#include <optional>
#include <string>
#include <system_error>

namespace art::seafire::protocol
{

  /// Implements a media type according to RFC 2046.
  ///
  class media_type_t
  {
  public:
    /// Media type parameters type.
    ///
    using params_t = std::map<std::string, std::string>;

    media_type_t();

    media_type_t(std::string, std::string);

    media_type_t(std::string,
                 std::string,
                 params_t);

    std::string const&
    type() const;

    std::string const&
    subtype() const;

    params_t const&
    params() const;

    template<typename InputIterator>
    static
    std::optional<media_type_t>
    try_parse(InputIterator&,
              InputIterator const&,
              std::error_code&);

    static
    std::optional<media_type_t>
    try_parse(std::string const&, std::error_code&);

  private:
    std::string type_;
    std::string subtype_;
    params_t params_;

  };

  bool
  operator==(media_type_t const&, media_type_t const&);

  bool
  operator!=(media_type_t const&, media_type_t const&);

  std::ostream&
  to_stream(std::ostream&, media_type_t const&);

  std::string
  to_string(media_type_t const&);

  std::ostream&
  operator<<(std::ostream&, media_type_t const&);

} // namespace art::seafire::protocol

#include <art/seafire/protocol/media-type.txx>

#endif
