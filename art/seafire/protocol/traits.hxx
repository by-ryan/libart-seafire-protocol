#ifndef art__seafire__protocol__traits_hxx_
#define art__seafire__protocol__traits_hxx_

#include <type_traits>

namespace art::seafire::protocol::traits
{

  /// Check if T has an alias type defined.
  ///
  template<typename, typename = std::void_t<>>
  struct has_alias_type
    : std::false_type
  {};

  template<typename T>
  struct has_alias_type<
    T,
    std::void_t<
      decltype(std::declval<typename T::alias_type>())
    >
  > : std::true_type
  {};

  /// Helper variable for has_alias_type.
  ///
  template<typename T>
  inline constexpr bool has_alias_type_v = has_alias_type<T>::value;

  /// Access the alias type of T, if available, otherwise T.
  ///
  template<typename T, bool = has_alias_type_v<T>>
  struct alias_type
  {
    using type = T;
  };

  template<typename T>
  struct alias_type<T, true>
  {
    using type = typename T::alias_type;
  };

  /// Helper for alias_type.
  ///
  template<typename T>
  using alias_type_t = typename alias_type<T>::type;

  template<typename, typename = std::void_t<>>
  struct has_overridden_to_string
    : std::false_type
  {};

  template<typename T>
  struct has_overridden_to_string<
    T,
    std::void_t<
      decltype(T::to_string(std::declval<alias_type_t<T>>()))
    >
  > : std::true_type
  {};

  template<typename T>
  inline constexpr bool has_overridden_to_string_v{
    has_overridden_to_string<T>::value
  };

} // art::seafire::protocol::traits

#endif
