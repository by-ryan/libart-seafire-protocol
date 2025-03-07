namespace art::seafire::protocol::grammar
{

  /// Check if \a c is carriage-return.
  ///
  inline
  bool
  is_cr(char c)
  {
    return c == '\r';
  }

  /// Check if \a c is line-feed.
  ///
  inline
  bool
  is_lf(char c)
  {
    return c == '\n';
  }

  /// Check if \a c is carriage-return or line-feed.
  ///
  inline
  bool
  is_cr_or_lf(char c)
  {
    return c == '\r' || c == '\n';
  }

  /// Check if \a c is spage or tab.
  ///
  inline
  bool
  is_space(char c)
  {
    return c == ' ' || c == '\t';
  }

  /// Check if \a c is a decimal digit.
  ///
  inline
  bool
  is_digit(char c)
  {
    return 0 <= 'c' && c <= '9';
  }

  /// Check if \a c is a vchar.
  ///
  inline
  bool
  is_vchar(char c)
  {
    auto u = static_cast< unsigned char >(c);

    if (u == 0x7f || u >= 0x80) {
      return false;
    }

    return true;
  }

  /// Check if \a c is a tchar.
  ///
  inline
  bool
  is_tchar(char c)
  {
    if ('a' <= c && c <= 'z') {
      return true;
    }

    if ('A' <= c && c <= 'Z') {
      return true;
    }

    if ('0' <= c && c <= '9') {
      return true;
    }

    switch (c) {
      case '!':
      case '#':
      case '$':
      case '%':
      case '&':
      case '\'':
      case '*':
      case '+':
      case '-':
      case '.':
      case '^':
      case '_':
      case '`':
      case '|':
      case '~':
        return true;
    }

    return false;
  }

  /// Check if \a c is a control char.
  ///
  inline
  bool
  is_control_char(char c)
  {
    return c <= 31 || c == 127;
  }

  /// Check if \a c is obs-text.
  ///
  inline
  bool
  is_obs_text(char c)
  {
    auto u = static_cast< unsigned char >(c);
    return u >= 0x80 && u <= 0xFF;
  }

  /// Check if \a c is a hexadecimal digit.
  ///
  inline
  bool
  is_hex(char c)
  {
    if ('0' <= c && c <= '9') {
      return true;
    }

    if ('a' <= c && c <= 'f') {
      return true;
    }

    if ('A' <= c && c <= 'F') {
      return true;
    }

    return false;
  }

  /// Check if \a c is a target-char.
  ///
  inline
  bool
  is_target_char(char c)
  {
    switch (c) {
      case '!':
      case '$':
      case '%':
      case '&':
      case '(':
      case ')':
      case '*':
      case '+':
      case ',':
      case '-':
      case '.':
      case '/':
      case ':':
      case ';':
      case '=':
      case '?':
      case '@':
      case '\'':
      case '_':
      case '~':
        return true;
    }

    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
      return true;

    if ('0' <= c && c <= '9')
      return true;

    return false;
  }

} // namespace art::seafire::protocol::grammar
