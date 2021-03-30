// Member functions for WordOccurrence
// Andrew Hughes
// 1/25/2020

#include <iostream>
#include "WordList.hpp"

using std::cout; using std::endl; using std::string;

// WordOccurence member functions 

WordOccurrence::WordOccurrence(const string& word, int num) {
  word_ = word; 
  num_ = num;
}

bool WordOccurrence::matchWord(const string & other) {
  return (this->word_ == other);
}
 
void WordOccurrence::increment() {
  ++num_;
}

string WordOccurrence::getWord() const {
  return word_;
}

int WordOccurrence::getNum() const {
  return num_;
}

bool equal(const WordOccurrence& w1, const WordOccurrence& w2) {
  return (w1.word_ == w2.word_ && w1.num_ == w2.num_);
}

// Comparator needed for sorting 
bool operator<(WordOccurrence const & a, WordOccurrence const & b)
{
  return a.num_ < b.num_;
}
