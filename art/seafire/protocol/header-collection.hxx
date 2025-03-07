#ifndef art__seafire__protocol__header_collection_hxx_
#define art__seafire__protocol__header_collection_hxx_

#include <map>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace art::seafire::protocol
{

  /// Represents a collection of HTTP headers.
  ///
  class header_collection_t
  {
  public:
    /// Iterator type.
    ///
    using const_iterator = std::multimap<std::string, std::string>::const_iterator;

    void
    set(std::string, std::string);

    void
    append(std::string, std::string);

    void
    erase(std::string);

    bool
    contains(std::string) const;

    std::vector<std::string>
    get(std::string) const;

    std::optional<std::string>
    get_one(std::string) const;

    const_iterator
    begin() const;

    const_iterator
    cbegin() const;

    const_iterator
    end() const;

    const_iterator
    cend() const;

    static
    void
    normalize(std::string&);

  private:
    std::multimap<std::string, std::string> kv_store_;
  };

  std::ostream&
  operator<<(std::ostream&, header_collection_t const&);

} // namespace art::seafire::protocol

#endif
