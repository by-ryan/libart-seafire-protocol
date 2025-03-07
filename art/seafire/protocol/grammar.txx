namespace art::seafire::protocol::grammar
{

  /// Skip space.
  ///
  template<typename InputIterator>
  void
  skip_space(InputIterator& it, InputIterator const& end)
  {
    while (it != end && is_space(*it)) {
      ++it;
    }
  }

} // namespace art::seafire::protocol::grammar
