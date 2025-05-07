#ifndef WORD_FREQUENCY_HXX
#define WORD_FREQUENCY_HXX

///////////////////////// TO-DO (1) //////////////////////////////
#include <unordered_map>
#include <string>
#include <string_view>
#include <istream>
#include <numeric>
#include <locale>
/////////////////////// END-TO-DO (1) ////////////////////////////







// anonymous, unnamed namespace providing non-member private working area
namespace
{
  std::string sanitize( std::string_view word )
  {
    constexpr char bad_char[] = " \t\r\n\b\v_-\"'(){}+/*,=.!?:;";                     // leading and trailing characters to be removed
    static std::locale locality{ "en_GB.UTF-8" };

    auto startIndex = word.find_first_not_of( bad_char );                             // start with the first non-bad character
    if( startIndex == std::string_view::npos ) startIndex = word.size();              // if the word contains only bad characters ...

    std::size_t count    = 0;                                                         // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );                         // end with the first non-bad character

    if( endIndex != std::string_view::npos ) count = endIndex - startIndex + 1;       // number of characters to use in results

    std::string result{ word.substr( startIndex, count ) };                           // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );                         // convert to lower case

    return result;                                                                    // result is moved optimized (copy elision) to the caller, std::move( result ) not required
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
template<typename Hasher>
WordFrequency<Hasher>::WordFrequency( std::istream & iStream )
{
  std::string token;
  while( iStream >> token )
  {
    auto clean = sanitize( token );
    if( !clean.empty() ) ++words_[ clean ];
  }
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::numberOfWords() const
{
  return words_.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::wordCount( std::string_view word ) const
{
  auto clean = sanitize( word );
  auto it    = words_.find( clean );
  return ( it == words_.end() ) ? 0 : it->second;
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
template<typename Hasher>
std::string WordFrequency<Hasher>::mostFrequentWord() const
{
  if( words_.empty() ) return {};

  auto best = words_.begin();
  for( auto it = std::next( words_.begin() ); it != words_.end(); ++it )
  {
    if( it->second > best->second ) best = it;
  }
  return best->first;
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::maxBucketSize() const
{
  std::size_t maxSize = 0;
  for( std::size_t i = 0; i < words_.bucket_count(); ++i )
  {
    maxSize = std::max( maxSize, words_.bucket_size( i ) );
  }
  return maxSize;
}
/////////////////////// END-TO-DO (6) ////////////////////////////







// Implement WordFrequency::bucketSizeAverage() const - See requirements
///////////////////////// TO-DO (7) //////////////////////////////
template<typename Hasher>
double WordFrequency<Hasher>::bucketSizeAverage() const
{
  auto buckets = words_.bucket_count();
  if( buckets == 0 ) return 0.0;
  return static_cast<double>( words_.size() ) / static_cast<double>( buckets );
}
/////////////////////// END-TO-DO (7) ////////////////////////////




#endif    // WORD_FREQUENCY_HXX
