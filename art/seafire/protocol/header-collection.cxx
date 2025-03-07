#include <art/seafire/protocol/header-collection.hxx>

#include <locale>

namespace art::seafire::protocol
{

  /// Set a header.
  ///
  /// Calling set
  void
  header_collection_t::
  set(std::string key, std::string value)
  {
    normalize(key);
    kv_store_.erase(key);
    kv_store_.emplace(std::move(key), std::move(value));
  }

  /// Append a header value.
  ///
  void
  header_collection_t::
  append(std::string key, std::string value)
  {
    normalize(key);
    kv_store_.emplace(std::move(key), std::move(value));
  }

  /// Erase a header.
  ///
  void
  header_collection_t::
  erase(std::string key)
  {
    normalize(key);
    kv_store_.erase(key);
  }

  /// Check if this collection contains a header.
  ///
  bool
  header_collection_t::
  contains(std::string key) const
  {
    normalize(key);
    return kv_store_.find(key) != kv_store_.end();
  }

  /// Get a header.
  ///
  std::vector<std::string>
  header_collection_t::
  get(std::string key) const
  {
    normalize(key);

    std::vector<std::string> strings;

    auto lower = kv_store_.lower_bound(key);
    auto upper = kv_store_.upper_bound(key);

    while (lower != upper) {
      strings.push_back(lower->second);
      ++lower;
    }

    return strings;
  }

  /// Get a header.
  ///
  std::optional<std::string>
  header_collection_t::
  get_one(std::string key) const
  {
    normalize(key);

    auto lower = kv_store_.lower_bound(key);
    auto upper = kv_store_.upper_bound(key);

    if (lower != upper)
      return lower->second;

    return {};
  }

  header_collection_t::const_iterator
  header_collection_t::
  begin() const
  {
    return kv_store_.begin();
  }

  header_collection_t::const_iterator
  header_collection_t::
  cbegin() const
  {
    return kv_store_.cbegin();
  }

  header_collection_t::const_iterator
  header_collection_t::
  end() const
  {
    return kv_store_.end();
  }

  header_collection_t::const_iterator
  header_collection_t::
  cend() const
  {
    return kv_store_.cend();
  }

  /// Normalize header name.
  ///
  void
  header_collection_t::
  normalize(std::string& name)
  {
    std::locale loc{ "C" };

    for (auto& c : name)
      c = std::tolower(c, loc);
  }

  /// Write headers to an output stream.
  ///
  std::ostream&
  operator<<(std::ostream& o, header_collection_t const& h)
  {
    for (auto const& j : h)
      o << j.first << " = " << j.second << '\n';

    return o;
  }

} // namespace art::seafire::protocol
