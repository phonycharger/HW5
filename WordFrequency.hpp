#ifndef WORD_FREQUENCY_HPP
#define WORD_FREQUENCY_HPP

///////////////////////// TO-DO (1) //////////////////////////////
#include <unordered_map>
#include <string>
#include <string_view>
#include <istream> 
/////////////////////// END-TO-DO (1) ////////////////////////////




template<typename Hasher = std::hash<std::string>>
class WordFrequency
{
  public:
    // Construction and assignment
    WordFrequency( std::istream & iStream = std::cin );                 // (default) constructor, add words from file to hash table


    // Accessors, Queries, and Observers
    std::size_t numberOfWords    (                       ) const;       // returns the number of unique words
    std::size_t wordCount        ( std::string_view word ) const;       // returns the number of occurrences of the given word
    std::string mostFrequentWord (                       ) const;       // returns the most frequent word
    std::size_t maxBucketSize    (                       ) const;       // returns the size of the largest bucket in the hash table
    double      bucketSizeAverage(                       ) const;       // returns the average number of elements per bucket


  private:
    // Instance Attributes - See requirements
    ///////////////////////// TO-DO (2) //////////////////////////////
std::unordered_map<std::string, std::size_t, Hasher> words_;
    /////////////////////// END-TO-DO (2) ////////////////////////////
};




#include "WordFrequency.hxx"



#endif    // WORD_FREQUENCY_HPP
