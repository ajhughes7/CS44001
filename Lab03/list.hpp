// node class tempate used to contruct lists
// Andrew Hughes
// 2/02/2020

#ifndef LIST_HPP_
#define LIST_HPP_

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class Node{
public:

  Node(): next_(nullptr) {}

  // functions can be inlined
  T getData()const{return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  Node<T>* getNext() const;
  void setNext(Node<T> *const);

private:
  T data_;
  Node<T> *next_;
};

//
// member functions for node
//
template <typename T>
Node<T>* Node<T>::getNext()const{
  return next_;
}

template<typename T>
void Node<T>::setNext(Node<T> *const next){
  next_=next;
}

#endif // LIST_HPP_
