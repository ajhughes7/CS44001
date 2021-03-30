// WordList member functions
// Andrew Hughes
// 1/25/2020

#include <iostream>
#include <algorithm>
#include "WordList.hpp"

using std::cout; using std::endl; using std::string;

// WordList member functions

WordList::WordList() {
  size_ = 0;
  wordArray_ = nullptr;
}

//copy constructor, destructor, overloaded assignment

WordList::WordList(const WordList& wl) {
  size_ = wl.size_;
  wordArray_ = new WordOccurrence[size_];
  for(int i=0; i < size_; ++i)
    wordArray_[i] = wl.wordArray_[i];
}

WordList::~WordList() {
  delete [] wordArray_; 
} 

// Source: https://stackoverflow.com/questions/3279543
void swap(WordList& first, WordList& second) {
  // enable ADL (not necessary in our case, but good practice)
  using std::swap;

  // by swapping the members of two objects,
  // the two objects are effectively swapped
  swap(first.size_, second.size_);
  swap(first.wordArray_, second.wordArray_);
}

WordList& WordList::operator=(WordList rhs) {
  swap(*this, rhs);
  return (*this);
}

bool equal(const WordList& w1, const WordList& w2) {
  if (w1.size_ != w2.size_)
    return false;
  for (int i = 0; i < w1.size_; ++i) {
    if (!equal(w1.wordArray_[i], w2.wordArray_[i]))
      return false;
  }
  return true;
}

void WordList::addWord(const string & insert) {
  // check if word previously added
  for (int i = 0; i < size_; ++i) {
    if (wordArray_[i].matchWord(insert)) {
      wordArray_[i].increment();
      return;
    }
  }
  // Word not found, need to add
  WordOccurrence *tempWordArray_ = new WordOccurrence [size_ + 1];
  for(int i=0; i < size_; ++i)
    tempWordArray_[i] = wordArray_[i];
  if (size_ > 0)
    delete [] wordArray_;
  tempWordArray_[size_++] = WordOccurrence(insert, 1);
  wordArray_ = tempWordArray_;
}

void WordList::print() {
  // sort wordArray_ by wordArray_[i].num_
  std::sort(wordArray_, wordArray_ + size_);
  for (int i = 0; i < size_; ++i) {
    WordOccurrence wo = wordArray_[i];
    cout << wo.getWord() << " " << wo.getNum() << endl;
  }
}
