// drink class to be used in Coffee Shack lab
// Andrew Hughes
// 04/13/2020

#include <string>
#include <set>
#include <vector>

using std::cout; using std::endl; using std::cin; using std::string;
using std::vector; using std::set;

enum class DrinkType {small, medium, large};

class Drink{
 public:
  Drink(DrinkType type= DrinkType::small, int price= 0):
    price_(price), type_(type) {}
  virtual int getPrice() const;
  virtual std::string getName() const;
 private: 
  int price_;
  DrinkType type_;
};

class Small: public Drink {
public:
  Small() {}
  int getPrice() const override {
    return 100;
  }
  string getName() const override {
    return "small";
  }
};


class Medium: public Drink {
public:
  Medium() {}
  int getPrice() const override {
    //    return drink_->getPrice() + 200;
    return 200;
  }
  string getName() const override {
    return "medium";
  }
};

class Large: public Drink {
public:
  Large() {}
  int getPrice() const override {
    return 300;
  }
  string getName() const override {
    return "large";
  }
};

class Sprinkles: public Drink {
public:
  Sprinkles(const Drink *drink){
    drink_ = drink;
  }
  int getPrice() const override {
    return drink_->getPrice() + 50;
  }
  string getName() const override {
    return "sprinkles";
  }
private:  
  const Drink* drink_;
};

class Caramel: public Drink {
public:
  Caramel(const Drink *drink){
    drink_ = drink;
  }
  int getPrice() const override {
    return drink_->getPrice() + 20;
  }
  string getName() const override {
    return "caramel";
  }
private:  
  const Drink* drink_;
};

class MilkFoam: public Drink {
public:
  MilkFoam(const Drink *drink){
    drink_ = drink;
  }
  int getPrice() const override {
    return drink_->getPrice() + 40;
  }
  string getName() const override {
    return "foam";
  }
private:  
  const Drink* drink_;
};

class Ice: public Drink {
public:
  Ice(const Drink *drink){
    drink_ = drink;
  }
  int getPrice() const override {
    return drink_->getPrice() + 10;
  }
  string getName() const override {
    return "ice";
  }
private:  
  const Drink* drink_;
};

class Observer {
public:
  Observer(class Subject* s);
  virtual void notify() const = 0;
};

class Subject{
public: 
  void registerObserver(Observer *o)
  {views_.insert(o);}
  void deregisterObserver(Observer *o)
  {views_.erase(o);}
  void notifyObservers() const {
    for(auto e: views_) e->notify();}
private:
  set <Observer *> views_;
};

class Barista; 

class Customer: public Observer {
public: 
  Customer(const string&, Barista*);
  void notify() const override; 
  char getDrinkSize() {
    return drinkSize_;
  }
  int getToppingNum() {
    return toppingNum_;
  }
  vector<char> getToppings() {
    return toppings_;
  }

private:
  char drinkSize_;
  int toppingNum_;
  vector<char> toppings_;
  string name_;
  Barista *s_;
};

  class Barista: public Subject {
  public:
    Barista(Barista *nextUp = nullptr) {
      nextUp_ = nextUp;
    }
    void orderUp(string drink) {
      drink_ = drink;
      notifyObservers();
    }
      const string& getDrink() const {
	return drink_;
      }
      virtual void handleRequest(char prefTopping, string result) {
	if (nextUp_ != nullptr)
	  nextUp_ -> handleRequest(prefTopping, result);
      }
  private: 
    Barista* nextUp_;
    string drink_;
  };

class JuniorBarista: public Barista {
public: 
  JuniorBarista(Barista* nextUp = nullptr): Barista(nextUp) {}
  void handleRequest(char prefTopping, string result) override {
    if (prefTopping == 'n') 
      cout << "Junior Bursita makes " << result << endl;
    else 
      Barista::handleRequest(prefTopping, result); 
  }
};

class SeniorBarista: public Barista {
public: 
  SeniorBarista(Barista* nextUp = nullptr): Barista(nextUp) {}
  void handleRequest(char prefTopping, string result) override {
    if (prefTopping != 'f') 
      cout << "Senior Bursita makes " << result << endl;
    else 
      Barista::handleRequest(prefTopping, result); 
  }
};

class Manager: public Barista {
public: 
  Manager(Barista* nextUp = nullptr): Barista(nextUp) {}
  void handleRequest(char prefTopping, string result) override {
    (void) prefTopping;
      cout << "Manager makes " << result << endl;
  }
};
