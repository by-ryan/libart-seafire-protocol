#ifndef art__seafire__protocol__message_hxx_
#define art__seafire__protocol__message_hxx_

#include <art/seafire/protocol/header-collection.hxx>
#include <art/seafire/protocol/protocol-version.hxx>
#include <art/seafire/protocol/traits.hxx>

#include <optional>
#include <ostream>

namespace art::seafire::protocol
{

  /// Common base class for HTTP messages.
  ///
  class message_t
  {
  public:
    message_t();

    explicit
    message_t(version_t);

    version_t const&
    version() const;

    void
    set_version(version_t);

    header_collection_t const&
    headers() const;

    void
    set_headers(header_collection_t);

    void
    set_header(std::string, std::string);

    void
    append_header(std::string, std::string);

    void
    erase_header(std::string);

  private:
    version_t version_;
    header_collection_t headers_;

  };

  template<typename Header>
  bool
  has(message_t const& m);

  template<typename Header>
  bool
  has_quick(message_t const& m);

  template<typename Header>
  std::optional<traits::alias_type_t<Header>>
  get(message_t const& m);

  template<typename Header>
  std::optional<traits::alias_type_t<Header>>
  get(message_t const& m, std::error_code& ec);

  template<typename Header, typename... Args>
  void
  set(message_t& m, Args&&... args);

  template<typename Header, typename... Args>
  void
  set_if_not_set(message_t& m, Args&&... args);

  template<typename Header>
  void
  erase(message_t& m);

  std::ostream&
  operator<<(std::ostream& o, message_t const& m);

} // namespace art::seafire::protocol

#include <art/seafire/protocol/message.txx>

#endif
