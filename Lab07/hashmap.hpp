// implementation basic hashmap (unordered container)
// Andrew Hughes
// 03/01/2020

#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
  DefaultHash(size_t numBuckets = defaultNumBuckets);
  size_t hash(const T& key) const;
  size_t numBuckets() const { return numBuckets_; }
  
private:
  // default number of buckets in the hash
  static const size_t defaultNumBuckets = 101;
  size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
  size_t res = 0;
  for (size_t i = 0; i < sizeof(key); ++i) {
    const unsigned char b =
      *(reinterpret_cast<const unsigned char *>(&key) + i);
    res += b;
  }
  return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value,
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap{

public:
  typedef pair<const Key, Value> Element;
  typedef pair<Value*, bool> InsertRet;
  typedef pair<Element*, bool> EraseRet;

  // constructor
  // invokes constructors for comparison and hash objects
  hashmap(const Compare& comp = Compare(),
          const Hash& hash = Hash());

  Element* find(const Key& x);      // returns pointer to element with key x,
  // nullptr if not found
  //pair<Value, bool> insert(const Element& x);    // inserts the key/value pair
  InsertRet insert(const Element& x);    // inserts the key/value pair
  EraseRet erase(const Key& x);         // erases element with key x, if exists
  Value& operator[] (const Key& x); // returns reference on value of
  // element with key, inserts if does not exist

  void rehash(size_t n); // resizes hash table and rearranges the elements

private:

  // helper function for various searches
  typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

  size_t size_;   // number of elements in the container
  Compare comp_;  // comparison functor, equal_to by default
  Hash hash_;     // hash functor

  // hash contents: vector of buckets
  // each bucket is a list containing key->value pairs
  vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(
                                            const Compare& comp, const Hash& hash):
  size_(0), comp_(comp), hash_(hash) {
  elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value,
          typename Compare, typename Hash>
typename list<pair<const Key, Value>>::iterator // return type
hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

  // look for the key in the bucket
  for (auto it =  elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
    if (comp_(it->first, x))
      return it;

  return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

  size_t bucket = hash_.hash(x);
  auto it=findElement(x, bucket);    // use the findElement() helper  

  if (it != elems_[bucket].end())
    // found the element. Return a pointer to it.
    return &(*it); // dereference the iterator to list
  // then take the address of list element
   
  else // didn't find the element -- return nullptr
    return nullptr;
}

template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::InsertRet // return value type
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {
    
  size_t bucket = hash_.hash(x.first);
  auto it = findElement(x.first, bucket);    // try to find the element
    
  // if not found, insert a new one.
  if (it == elems_[bucket].end()) {
    ++size_;
    elems_[bucket].push_back(x);
    return make_pair(&(elems_[bucket].back().second), true); // true because insert is good
  }
  return make_pair(&(it->second), false); // false because element already exsit
}



/*
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::InsertRet // return value type
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {
  // std::cout << "insert( " << x.first <<"," << x.second << ")"  << std::endl;

  size_t bucket = hash_.hash(x.first);  
  auto it = findElement(x.first, bucket);    // try to find the element

  // if not found, insert a new one.
  if (it == elems_[bucket].end()) {
    ++size_;
    Element e = pair<Key,Value>(x.first,x.second);
    elems_[bucket].push_back(e);
    //Value *vPtr = new Value(e.second);
    auto it2 = elems_[bucket].end();
    return make_pair(&(elems_[bucket].end().second), true);
    //    return make_pair(&e.second, true);
  }
  return make_pair(&(it->second), false);
}
*/

// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::EraseRet
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {

  size_t bucket = hash_.hash(x);
  auto it = findElement(x, bucket);    // try to find the element
  if (it != elems_[bucket].end()) {    // the element exists, erase it
    auto itRet = elems_[bucket].erase(it);
    --size_;
    
    if (itRet == elems_[bucket].end()) {
      size_t i = bucket + 1;
      while (i < elems_.size()) {
	if (!elems_[i].empty())
	  return make_pair(&(*elems_[i].begin()), true);
	++i;
      }
      return make_pair(nullptr, true);
    } else 
      return make_pair(&(*it), true);
  }
  return make_pair(nullptr, false);
}

    
/*
// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
pair<Value*, bool> hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {

  size_t bucket = hash_.hash(x);
  auto it = findElement(x, bucket);    // try to find the element
  if (it != elems_[bucket].end()) {    // the element exists, erase it
    elems_[bucket].erase(it);
    --size_;
  }
}

*/

/*
// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

  Element* found = find(x);
  if (found == nullptr) { // if key not found, create new element with empty value
    insert(make_pair(x, Value())); // calling default constructor on Value
    found = find(x); // inefficient but avoids code duplication
  }
  return found->second;
}
*/

// See https://stackoverflow.com/questions/47849339/how-can-i-have-a-pair-with-reference-inside-vector

// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& k) {

  Element* found = find(k);
  if (found == nullptr) { // if key not found, create new element with empty value
    InsertRet safe = insert(make_pair(k, Value())); // calling default constructor on Value
    return *safe.first;
  }
  return found->second;
}

// resizes hash table and rearranges the elements
template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {
  if (n <= size_)
    return;
  elems_.resize(n);
  
  hash_ = DefaultHash<Key>(n);

  for(size_t i = 0; i < elems_.size(); i++)
    for (auto it =  elems_[i].begin(); it != elems_[i].end();) {
      Element temp = make_pair(it->first, it->second);
      elems_[i].erase(it++);
      insert(temp);
    }
  size_ = n;
}

