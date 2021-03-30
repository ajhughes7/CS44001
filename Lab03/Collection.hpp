// Collection class template
// Andrew Hughes
// 02/3/2020

#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include "list.hpp"
#include <iostream>

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class Collection {
public: 
  Collection() : list_(nullptr) {};
  void add(const T item); 
  void remove(const T item); 
  T last();
  void print();
  friend bool equal(const Collection<T> &c1, const Collection<T> &c2) {
    Node<T> *c1Ptr = c1.list_;
    Node<T> *c2Ptr = c2.list_;
    while (c1Ptr != nullptr && c2Ptr != nullptr) {
      if (c1Ptr->getData() != c2Ptr->getData())
	return false;
      c1Ptr = c1Ptr->getNext();
      c2Ptr = c2Ptr->getNext();
    }
    return (c1Ptr == nullptr && c2Ptr == nullptr);  
  }
private:
  Node<T> *list_;
};

// item will be added to end of Collection
template <typename T>
void Collection<T>::add(const T item) {
  Node<T> *newNodePtr = new Node<T>();
  newNodePtr->setData(item);
  newNodePtr->setNext(nullptr);
  if (list_ == nullptr) {
    list_ = newNodePtr;
    return;
  }
  Node<T> *nPtr = list_;
  while (nPtr->getNext() != nullptr) {
    nPtr = nPtr->getNext();
  }
  // nPtr points to last node
  nPtr->setNext(newNodePtr);
}

/*
// Prepend adding of item
template <typename T>
void Collection<T>::add(const T item) {
  Node<T> *nPtr = new Node<T>();
  nPtr->setData(item);
  nPtr->setNext(list_);
  list_ = nPtr;
}
*/

template <typename T>
void Collection<T>::remove(const T item) {
  Node<T> *curPtr = list_;
  Node<T> *prevPtr = curPtr;
  while (curPtr && curPtr->getData() != item) {
    prevPtr = curPtr;
    curPtr = prevPtr->getNext();
  }
  if (curPtr == nullptr)
    return; // item is not found
  // item found at curPtr
  if (curPtr == list_)
    list_ = curPtr->getNext();
  else 
    prevPtr->setNext(curPtr->getNext());
  delete curPtr;
}

template <typename T>
void Collection<T>::print() {
  Node<T> *nPtr = list_;
  while (nPtr != nullptr) {
    std::cout << nPtr->getData() << " -> ";
    nPtr = nPtr->getNext();
  }
  std::cout << std::endl;
}

// returns last element of list
// WARNING: assumes there are elements in list
template <typename T>
T Collection<T>::last() {
  Node<T> *nPtr = list_;
  /*
  if (!nPtr)
      return nullptr; */
  while (nPtr && nPtr->getNext()) {
    nPtr = nPtr->getNext();
  }
  return nPtr->getData();
}



#endif // COLLECTION_HPP_
