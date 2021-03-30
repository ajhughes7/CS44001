// sorting oranges
// converting vectors to multimaps
// Andrew Hughes
// 2/21/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;
using std::pair;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
  Variety v;
  string color; // red, green or orange
};


int main(){
  srand(time(nullptr));
  multimap<Variety, Fruit> tree;
  int numEntries = rand()%100+1;
  for (int i = 0; i < numEntries; ++i) {
    Fruit f;
    f.v = static_cast<Variety>(rand() % 3);
    f.color = colors[rand()%3];
    tree.insert(pair<Variety, Fruit> (f.v, f));
  }
  cout << "Colors of the oranges: ";
  for(auto f=tree.lower_bound(Variety::orange); f!=tree.upper_bound(Variety::orange); ++f)
    cout << f->second.color << ", ";
  cout << endl;
}
