#ifndef art__seafire__protocol__grammar_hxx_
#define art__seafire__protocol__grammar_hxx_

namespace art::seafire::protocol::grammar
{

  bool
  is_cr(char c);

  bool
  is_lf(char c);

  bool
  is_cr_or_lf(char c);

  bool
  is_space(char c);

  bool
  is_digit(char c);

  bool
  is_vchar(char c);

  bool
  is_tchar(char c);

  bool
  is_control_char(char c);

  bool
  is_obs_text(char c);

  bool
  is_hex(char c);

  bool
  is_target_char(char c);

  template<typename InputIterator>
  void
  skip_space(InputIterator& it, InputIterator const& end);

} // namespace art::seafire::protocol::grammar

#include <art/seafire/protocol/grammar.ixx>
#include <art/seafire/protocol/grammar.txx>

#endif
