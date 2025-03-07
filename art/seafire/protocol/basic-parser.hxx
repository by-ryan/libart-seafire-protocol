#ifndef art__seafire__protocol__basic_parser_hxx_
#define art__seafire__protocol__basic_parser_hxx_

#include <art/seafire/protocol/error.hxx>
#include <art/seafire/protocol/grammar.hxx>
#include <art/seafire/protocol/message.hxx>
#include <art/seafire/protocol/protocol-version.hxx>
#include <art/seafire/protocol/request.hxx>
#include <art/seafire/protocol/response.hxx>

#include <art/uri/uri.hxx>

#include <stdexcept>
#include <vector>

namespace art::seafire::protocol
{

  /// Implements a basic HTTP message parser.
  ///
  template<typename Iterator>
  class basic_parser_t {
  public:
    /// Holds an iterator pair.
    ///
    struct iterator_pair_t
    {
      Iterator first;
      Iterator last;
    };

    /// Holds iterator pairs for a header/value.
    ///
    struct header_t
    {
      iterator_pair_t field;
      iterator_pair_t value;
    };

    /// Attempt to parse a message.
    ///
    Iterator
    parse(Iterator, Iterator, std::error_code&);

    iterator_pair_t const&
    version() const
    {
      return version_;
    }

    std::vector<header_t> const&
    headers() const
    {
      return headers_;
    }

  protected:
    enum expectation_t
    {
      // Requests.
      //
      expect_method_start = 10,
      expect_method,

      expect_target_start = 20,
      expect_target,

      expect_version_h = 30,
      expect_version_ht,
      expect_version_htt,
      expect_version_http,
      expect_version_slash,
      expect_version_major,
      expect_version_period,
      expect_version_minor,
      expect_version_cr,
      expect_version_lf,

      // Response
      //
      expect_response_version_h,
      expect_response_version_ht,
      expect_response_version_htt,
      expect_response_version_http,
      expect_response_version_slash,
      expect_response_version_major,
      expect_response_version_period,
      expect_response_version_minor,
      expect_response_version_space,

      expect_response_status_1,
      expect_response_status_2,
      expect_response_status_3,
      expect_response_status_space,

      expect_response_reason_start,
      expect_response_reason,
      expect_response_reason_lf,

      // Headers.
      //
      expect_header_start = 100,
      expect_header_field,
      expect_header_value_start,
      expect_header_value,
      expect_header_terminating_lf,

      expect_terminating_lf,

      done = 9999

    };

    /// Construct a new parser.
    ///
    explicit
    basic_parser_t(expectation_t expect)
      : expect_{expect}
    {}

    /// Copy-construct a new parser.
    ///
    basic_parser_t(basic_parser_t const&) = default;

    /// Move-construct a new parser.
    ///
    basic_parser_t(basic_parser_t&&) = default;

    /// Copy-assign this parser.
    ///
    basic_parser_t&
    operator=(basic_parser_t const&) = default;

    /// Move-assign this parser.
    ///
    basic_parser_t&
    operator=(basic_parser_t&&) = default;

    expectation_t expect_;

    iterator_pair_t method_;
    iterator_pair_t target_;
    iterator_pair_t version_;

    iterator_pair_t status_;
    iterator_pair_t reason_;

    std::vector<header_t> headers_;

  private:
    expectation_t
    parse_char(Iterator it, std::error_code&);

  };

  /// Implements a basic request parser.
  ///
  template<typename Iterator>
  class basic_request_parser_t
    : public basic_parser_t<Iterator>
  {
  public:
    basic_request_parser_t()
      : basic_parser_t<Iterator>{basic_parser_t<Iterator>::expect_method_start}
    {}

    typename basic_parser_t<Iterator>::iterator_pair_t const&
    method() const
    {
      return basic_parser_t<Iterator>::method_;
    }

    typename basic_parser_t<Iterator>::iterator_pair_t const&
    target() const
    {
      return basic_parser_t<Iterator>::target_;
    }
  };

  /// Implements a basic request parser.
  ///
  template<typename Iterator>
  class basic_response_parser_t
      : public basic_parser_t<Iterator>
  {
  public:
    basic_response_parser_t()
      : basic_parser_t<Iterator>{basic_parser_t<Iterator>::expect_response_version_h}
    {}

    typename basic_parser_t<Iterator>::iterator_pair_t const&
    status() const
    {
      return basic_parser_t<Iterator>::status_;
    }

    typename basic_parser_t<Iterator>::iterator_pair_t const&
    reason() const
    {
      return basic_parser_t<Iterator>::reason_;
    }
  };

  template<typename Iterator>
  void
  extract_version(basic_parser_t<Iterator> const&, message_t&);

  template<typename Iterator>
  void
  extract_headers(basic_parser_t<Iterator> const&, message_t&);

  template<typename Iterator>
  void
  extract_method(basic_request_parser_t<Iterator> const&, request_t&);

  template<typename Iterator>
  void
  extract_target(basic_request_parser_t<Iterator> const&, request_t&);

  template<typename Iterator>
  void
  extract_status(basic_response_parser_t<Iterator> const&, response_t&);

  template<typename Iterator>
  void
  extract_reason(basic_response_parser_t<Iterator> const&, response_t&);

  template<typename Iterator>
  void
  extract_message(basic_parser_t<Iterator> const&, message_t&);

  template<typename Iterator>
  void
  extract_message(basic_request_parser_t<Iterator> const&, request_t&);

  template<typename Iterator>
  void
  extract_message(basic_response_parser_t<Iterator> const&, response_t&);

  template<typename InputIterator>
  InputIterator
  parse_request(request_t&, InputIterator, InputIterator);

  template<typename InputIterator>
  InputIterator
  parse_request(request_t&,
                InputIterator,
                InputIterator,
                std::error_code&);

  template<typename InputIterator>
  InputIterator
  parse_request(request_t&,
                basic_request_parser_t<InputIterator>&,
                InputIterator,
                InputIterator);

  template<typename InputIterator>
  InputIterator
  parse_request(request_t&,
                basic_request_parser_t<InputIterator>&,
                InputIterator,
                InputIterator,
                std::error_code&);

  template<typename InputIterator>
  InputIterator
  parse_response(response_t&,
                 InputIterator,
                 InputIterator,
                 std::error_code&);

  template<typename InputIterator>
  InputIterator
  parse_response(response_t&,
                 basic_response_parser_t<InputIterator>&,
                 InputIterator,
                 InputIterator);

  template<typename InputIterator>
  InputIterator
  parse_response(response_t&,
                 basic_response_parser_t<InputIterator>&,
                 InputIterator,
                 InputIterator,
                 std::error_code&);

  class parser_not_ready
    : public std::logic_error
  {
  public:
    parser_not_ready()
      : std::logic_error{"parser not ready"}
    {}

  };

} // namespace art::seafire::protocol

#include <art/seafire/protocol/basic-parser.txx>

#endif
