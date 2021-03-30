//
// Andrew Hughes
// 04/13/2020


#include <iostream>
#include <iomanip>
#include "drink.hpp"

using std::cout; using std::endl; using std::cin; using std::string;

int Drink::getPrice() const {
  return price_;
}

string Drink::getName() const {
  return "";
}

void Customer::notify() const {
  std::cout << "Customer " << name_ << " checks if "
	    << "Barista made their drink..." << std::endl;
}

Observer::Observer(Subject *s){
  s->registerObserver(this);
}

Customer::Customer (const string &name, Barista* s):
  name_(name), s_(s), 
  Observer(static_cast<Subject*>(s)){}

int main () {
  bool customerNotified = false;
  bool demoPartOne = false;

  srand((unsigned)time(nullptr));
  Barista *manager = new Manager();
  Barista *senior = new SeniorBarista(manager);
  Barista *junior = new JuniorBarista(senior);
  
  do {
    string fullOrder = "";
    Drink startDrink;    
    int totalCost = 0;
    cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    char size;
    cin >> size;
    
    switch (size) {
    case 's':
      fullOrder += Small().getName() + " coffee with "; 
      totalCost += Small().getPrice();
      break;
    case 'm':
      fullOrder += Medium().getName() + " coffee with "; 
      totalCost += Medium().getPrice();
      break;
    case 'l':
      fullOrder += Large().getName() + " coffee with "; 
      totalCost += Large().getPrice();
      break;
    }
 
    char prefTopping = 'n';      
    char extras;
    do {      
      cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
      cin >> extras; 
            
      switch (extras) {
      case 's':
	fullOrder += Sprinkles(&startDrink).getName() + ", ";
	totalCost += Sprinkles(&startDrink).getPrice();
	if (prefTopping != 'f') prefTopping = 's';
	break;
      case 'c':
	fullOrder += Caramel(&startDrink).getName() + ", ";
	totalCost += Caramel(&startDrink).getPrice();
	if (prefTopping != 'f') prefTopping = 's';
	break;
      case 'f':
	fullOrder += MilkFoam(&startDrink).getName() + ", ";
	totalCost += MilkFoam(&startDrink).getPrice();
	prefTopping = 'f';
	break;
      case 'i':
	fullOrder += Ice(&startDrink).getName() + ", ";
	totalCost += Ice(&startDrink).getPrice();
	if (prefTopping != 'f') prefTopping = 's';
	break;  
      }
    } while (extras != 'n');
    cout << "Can I get your name? ";
    string name;
    cin >> name; 
    
    Customer *customer = new Customer(name, junior);
    junior->registerObserver(customer);
    junior->handleRequest(prefTopping, fullOrder);
    if (demoPartOne || rand() % 2) {
      customerNotified = true; 
      cout << name << ", your " << fullOrder << "is ready." << endl;
      cout << "Your total is $" << std::fixed << std::setprecision(2) 
	   << std::setfill('0')
	   << totalCost / 100.0 << endl;
      junior->notifyObservers();
    }
  } while (!customerNotified);
  cout << "break time" << endl;
}
