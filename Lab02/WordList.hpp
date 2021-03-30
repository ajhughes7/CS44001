// Header file for WordList class 
// Andrew Hughes
// 1/25/2020

#include "WordOccurrence.hpp"

class WordList{
public:
  WordList();

  // add copy constructor, destructor, overloaded assignment

  WordList(const WordList&); // copy constructor 
  ~WordList(); // destructor 
  WordList& operator=(WordList); // overloaded assignment 
  
  friend void swap(WordList& first, WordList& second);

  // implement comparison as friend
  friend bool equal(const WordList&, const WordList&);

  void addWord(const std::string &);
  void print();
private:
  WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
  // may or may not be sorted
  int size_;
};
