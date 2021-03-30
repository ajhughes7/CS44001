// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Andrew Hughes
// 02/21/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;


struct Apple{
  double weight; // oz
  string color;  // red or green
  void print() const { cout << color << ", " <<  weight << endl; }
};

bool goodForJam(Apple a, double maxWeight);

int main(){
  srand(time(nullptr));
  const double minWeight = 8.;
  const double maxWeight = 3.;

  cout << "Input crate size: ";
  int size;
  cin >> size;

  vector <Apple> crate(size);

  // assign random weight and color to apples in the crate
  // replace with generate()
  generate(crate.begin(), crate.end(), [=] () {
      Apple a;
       a.weight = minWeight + 
	 static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
       a.color = rand() % 2 == 1 ? "green" : "red"; 
       return a;
     });
  for_each(crate.begin(), crate.end(), [](Apple a) {
      a.print();
    });

   /*
    for(auto it = crate.begin(); it != crate.end(); ++it){
      it->weight = minWeight + 
	static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      it->color = rand() % 2 == 1 ? "green" : "red";
  }
   */
  cout << "Enter weight to find: ";
  double toFind;
  cin >> toFind;

  // count_if()
  int cnt = count_if(crate.begin(), crate.end(), [toFind](Apple a) {
      return a.weight > toFind;
    });

  /*
  int cnt = 0;
  for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
    if(it->weight > toFind) ++cnt;
  */

  cout << "There are " << cnt << " apples heavier than " 
       << toFind << " oz" <<  endl;

  // find_if()
  /*
    Using for_each() instead of find_if() because 
    1. find_if() returns apples not indexes
    2. find_if() only returns the first not all
   */

  cout << "at positions ";
  int count = 0;
  for_each(crate.begin(), crate.end(), [&count, toFind](Apple a) {
      ++count;
      if (a.weight > toFind)
	cout << count << ", ";
    });
  cout << endl;

    /*
for(int i=0; i < size; ++i)
    if(crate[i].weight > toFind)
      cout << i << ", ";
  cout << endl;
    */

  // max_element()
  double heaviest = max_element(crate.begin(), 
				crate.end(), 
				[] (const Apple& lhs, const Apple& rhs) {
				  return lhs.weight < rhs.weight;
				    })->weight;
  cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;

/*
  double heaviest = crate[0].weight;
  for(int i=1; i < size; ++i)
    if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
  cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;
*/

  // for_each() or accumulate()
  double total = accumulate(crate.begin(), crate.end(), 0.0, [] (double sum, const Apple& a) {
      return sum + a.weight;
    });

    /*
  double sum = 0;
  for(int i=0; i < size; ++i)
    sum += crate[i].weight;
    */

  cout << "Total apple weight is: " << total << " oz" << endl;

  // transform();
  cout << "How much should they grow: ";
  double toGrow;
  cin >> toGrow;  
  transform(crate.begin(), crate.end(), crate.begin(), [toGrow] (Apple a) {
      Apple a2;
      a2.color = a.color;
      a2.weight = a.weight + toGrow;
      return a2;
	});

  for_each(crate.begin(), crate.end(), [](Apple a) {
      a.print();
    });

  /*
  for(unsigned long i=0; i < crate.size(); ++i)
    crate[i].weight += toGrow;
  */

  // remove_if()
  cout << "Input minimum acceptable weight: ";
  double minAccept;
  cin >> minAccept;
  crate.erase(remove_if(crate.begin(), crate.end(), [minAccept](const Apple& a) { 
      return a.weight < minAccept;
      }), crate.end());
   
    /*
  for(auto it=crate.begin(); it != crate.end(); )
    if(it->weight < minAccept)
      it = crate.erase(it);
    else
      ++it;
    */

  for_each(crate.begin(), crate.end(), [](Apple a) {
      a.print();
    });
  
  cout << "removed " << size - crate.size() << " elements" << endl;

  // bubble sort, replace with sort()
  sort(crate.begin(), crate.end(), 
       [](const Apple& a, const Apple& a1) -> bool
       { 
	 return a.weight < a1.weight; 
       });

  /*
  bool swapped;
  do{
    swapped = false;
    for(unsigned long i=0; i < crate.size()-1; ++i)
      if(crate[i].weight > crate[i+1].weight){
	std::swap(crate[i], crate[i+1]);
	swapped = true;
      }
  }while(swapped);

  for_each(crate.begin(), crate.end(), [](Apple a) {
      a.print();
    });
  */

  // moving all red apples from crate to peck
  // remove_copy_if() with back_inserter()/front_inserter() or equivalents
  deque<Apple> peck;
  std::remove_copy_if(crate.begin(), crate.end(), std::back_inserter(peck),
		      [] (Apple& a) -> bool {
			return a.color != "red";
		      });
  crate.erase(std::remove_if(crate.begin(),crate.end(), [](Apple &a) {
	return a.color == "red";
      }),crate.end());
    
  /*
  for(auto it=crate.begin(); it != crate.end();)
    if(it->color == "red"){
      peck.push_front(std::move(*it));
      it=crate.erase(it);
    }else
      ++it;
  */

  // for_each() possibly
  cout << "apples in the crate"<< endl;
  for_each(crate.begin(), crate.end(), [](Apple a) {
      a.print();
    });

  cout << endl;

  // for_each() possibly
  cout << "apples in the peck"<< endl;
  for_each(peck.begin(), peck.end(), [](Apple a) {
      a.print();
    });
  
   // prints every "space" apple in the peck
   // 
   const int space=3; 
   cout << "\nevery " << space << "\'d apple in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
 
   for(auto it=std::next(peck.begin(), space - 1); 
       std::distance(it, peck.end()) > space - 3;) { 
     it->print();
     std::advance(it, space);
   }
   
   /*
   auto it2=peck.cbegin(); int i = 0;   
   while(it2 != peck.cend()){
     if(i == space){
       it2->print();
       i=0;
     }
     ++i; 
     ++it2;
   }
   */

   // putting all small green apples in a jam
   // use a binder to create a functor with configurable max weight
   // count_if() then remove_if()
   const double weightToJam = 10.0;
   //   auto it = find_if(vect.begin(), vect.end(), 
   //		     bind(std::less<Apple>(), _1, 70));
   double jamWeight = accumulate(crate.begin(), crate.end(), 0.0, [weightToJam] (double sum, const Apple& a) {
       if (goodForJam(a, weightToJam))
	 return sum + a.weight;
      else 
	return sum;
     });
   crate.erase(std::remove_if(crate.begin(),crate.end(),
			      bind(goodForJam, std::placeholders::_1, 
				   weightToJam)),crate.end());

   cout << "With removal of apples used for jam: " << endl;
   for_each(crate.begin(), crate.end(), [](Apple a) {
      a.print();
    });

  /*
   for(auto it=crate.begin(); it != crate.end();)
      if(it->weight < weightToJam){
 jamWeight += it->weight;
 it=crate.erase(it);
      }else
 ++it;
   */

   cout << "Weight of jam is: " << jamWeight << endl;
}

bool goodForJam(Apple a, double maxWeight) {
  return a.weight < maxWeight;
}
