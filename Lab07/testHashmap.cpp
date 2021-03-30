// demoes hashmap implementation
// Andrew Hughes
// 03/01/2020

/*
  Updating Hash Container Implementation
  Lab Assignment

  The project is due in one week: by the midnight on the day of the
  next lab. Make sure to include your name in comments of the source
  files.  Use the implementation of the basic hashmap template that we
  studied and do the following modifications:

  - modify the implementation of insert() so that it provides "safe
    insert", i.e.: returns a pair: <pointer, result>, where

    - pointer is a pointer to the newly inserted value or the old
      value with the same key

    - result is a boolean value which is true if the element is
      inserted

  - on the basis of your updated insert() implementation, modify the
    implementation of the overloaded indexing operator [] to eliminate
    inefficient second invocation of find(). That is, in your
    implementation, find() should only be invoked once.

  - modify the implementation of erase() so that it returns a pair
    <pointer, result>, where

    - pointer is a pointer to the element past one erased. Note that
      if the next element in a different bucket, it should still be
      returned. In case the element with the key specified to erase()
      does not exist, the value of the returned pointer is
      unspecified. If erase() removes the last element of the
      container (the last element of the list of the last bucket),
      then erase() should return nullptr.

    - result is a boolean value which is true if the element is
      successfully erased; result is false if the element with the
      specified key is not present in the container.

  - implement void rehash(size_t n) sets the number of buckets in the
    container to n. Note that the existing elements need to be
    re-arranged according to their new hash value. Note also that
    Hash: the object that provides hashing, needs to be updated to
    contain the new number of buckets. If the parameter n is smaller
    than the current number of buckets, no actions need to be taken.

  Provide test code that declares and populates a container and then
  demonstrates the operation of the functions you implemented.

  Milestone: insert() modification.
*/

#include "hashmap.hpp"
#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using std::cin; using std::cout; using std::endl;
using std::string;

SCENARIO( "Original hashmap template behavior", "[hashmap]" ) {

  GIVEN( "A hashmap<int,int> with some inserted items" ) {
    hashmap<int, int> hashMap;
    hashMap.insert(pair<int,int>(4, 40));
    hashMap.insert(make_pair(6, 60));

    WHEN( "an inserted key is searched " ) {
      // valuePtr will have type hashmap<int, int>::value_type*
      auto valuePtr = hashMap.find(4);

      THEN( "it is found." ) {
        REQUIRE( valuePtr != nullptr );
        REQUIRE( valuePtr->second == 40 );
      }
    }
    WHEN( "an non-inserted key is searched " ) {
      auto valuePtr = hashMap.find(999);

      THEN( "it is not found." ) {
        REQUIRE( valuePtr == nullptr );
      }
    }
    WHEN( "an key is erased " ) {
      hashMap.erase(4);
      auto valuePtr = hashMap.find(4);

      THEN( "it is not found." ) {
        REQUIRE( valuePtr == nullptr );
      }
    }
    WHEN( "indexing operator is used to store a value " ) {
      hashMap[4] = 35;
      hashMap[4] = 60;

      auto valuePtr = hashMap.find(4);

      THEN( "it is found" ) {
        REQUIRE( valuePtr != nullptr );
      }
      THEN( "it is equal to the value last assigned to the index" ) {
        REQUIRE( valuePtr->second == 60 );
      }
    }
  }
  GIVEN( "A hashmap<int,string> with some inserted items" ) {
    hashmap<int, string> employees;

    employees[123] = "Mike";
    //employees.insert(make_pair(345, "Charlie")); // This works, but next line doesn't:
    employees[345] = "Charlie";
    employees[192] = "Joe";
    employees[752] = "Paul";
    employees[328] = "Peter";

    WHEN( "indexing operator is used to store a value " ) {
      auto valuePtr = employees.find(345);

      THEN( "it is found" ) {
        REQUIRE( valuePtr != nullptr );
      }
      THEN( "it has a retrieved key equal to the assigned key" ) {
        REQUIRE( valuePtr->first == 345 );
      }
      THEN( "it has a retrieved value equal to the assigned value" ) {
        REQUIRE( valuePtr->second == "Charlie" );
      }
    }
    WHEN( "erase is used to fire an employee " ) {
      employees.erase(345);

      THEN( "it is no longer found" ) {
        REQUIRE( employees.find(345) == nullptr );
      }
    }
    WHEN( "erase is used to fire the rest of the employees " ) {
      employees.erase(123);
      employees.erase(192);
      employees.erase(752);
      employees.erase(328);

      THEN( "Mike is gone" ) {
        REQUIRE( employees.find(123) == nullptr );
      }
      THEN( "Joe is gone" ) {
        REQUIRE( employees.find(192) == nullptr );
      }
      THEN( "Paul is gone" ) {
        REQUIRE( employees.find(752) == nullptr );
      }
      THEN( "Peter is gone" ) {
        REQUIRE( employees.find(328) == nullptr );
      }
    }
  }
}

SCENARIO( "Improved hashmap template behavior", "[hashmap]" ) {

  GIVEN( "A hashmap<int,int> with some inserted items" ) {
    hashmap<int, int> hashMap;

    WHEN( "a first value is inserted " ) {
      // vPair will have type hashmap<int, int>::value_type*
      auto vPair = hashMap.insert(pair<int,int>(4, 40));

      THEN( "the return value " ) {
        REQUIRE( *(vPair.first) == 40 );
        REQUIRE( vPair.second );
      }
    }
    WHEN( "a second value is inserted at the same key " ) {
      hashMap.insert(pair<int,int>(4, 40));
      auto vPair = hashMap.insert(pair<int,int>(4, 80));

      THEN( "the return value " ) {
        REQUIRE( *(vPair.first) == 40 );
        REQUIRE( !vPair.second);
      }
    }
  }
  GIVEN( "A hashmap<int,int> with some inserted items" ) {
    hashmap<int, int> hashMap;
    hashMap[1] = 10;
    hashMap[2] = 20;
    hashMap[3] = 30;
    hashMap[4] = 40;

    WHEN( "erasing an nonexisting element " ) {
      auto vPair = hashMap.erase(99);

      THEN( "false is returned in second" ) {
        REQUIRE( !vPair.second );
      } // and vPair.first is unspecified, so cnanot test
    }
    WHEN( "erasing an existing element (non-last position) " ) {
      auto vPair = hashMap.erase(1);

      THEN( "true is returned in second" ) {
        REQUIRE( vPair.second );
      }

      THEN( "next Element after erased " ) {
        REQUIRE( vPair.first->first == 2 );
        REQUIRE( vPair.first->second == 20 );
      }
    }
    WHEN( "erasing an existing element (non-last position) " ) {
      auto vPair = hashMap.erase(3);

      THEN( "true is returned in second" ) {
        REQUIRE( vPair.second );
      }

      THEN( "next Element after erased " ) {
        REQUIRE( vPair.first->first == 4 );
        REQUIRE( vPair.first->second == 40 );
      }
    }
    WHEN( "erasing an existing element (last position) " ) {
      auto vPair = hashMap.erase(4);

      THEN( "true is returned in second" ) {
        REQUIRE( vPair.second );
      }
      THEN( "nullptr is returned in first" ) {
        REQUIRE( vPair.first == nullptr );
      }
    }
  }
  GIVEN( "A hashmap<int,int> with some inserted items" ) {
    hashmap<int, int> hashMap;
    
    for (int i = 0; i < 200; ++i) {
      hashMap[i] = i * 10;
    }
    WHEN( "hashmap is resized" ) {
      hashMap.rehash(300);

      THEN( "all the elements are still present" ) {
	
	for (int i = 0; i < 200; ++i) {
	  REQUIRE(hashMap[i] == i * 10); 
	}
      }
    }
  }
}
