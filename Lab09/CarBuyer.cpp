//Andrew Hughes
// 4/3/2020

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl; using std::string;

class CarLot{
public:
  CarLot();
  Car *nextCar() {
    return lot_[rand() % lotSize()];
  }
  
  // if a car is bought, requests a new one
  Car *buyCar(Car *boughtCar){ 
    for (int i = 0; i < lotSize(); ++i) {
      if (lot_[i] == boughtCar) {
        lot_[i] = factories_[rand()%factories_.size()]->requestCar();
	break;
      }
    }
    return boughtCar;
  }
  
  int lotSize() {
    return 10;
  }
   
private:
  vector<Car*> lot_; // all cars in the lot
  vector<CarFactory *> factories_;
};


CarLot::CarLot(){
  // creates 2 Ford factories and 2 Toyota factories 
  factories_.push_back(new FordFactory());   
  factories_.push_back(new ToyotaFactory());
  factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());

  // initializes car lot
  for (int i = 0; i < lotSize(); ++i) {
    lot_.push_back(factories_[rand()%factories_.size()]->requestCar());
  }
}

CarLot *carLotPtr = nullptr; // global pointer instantiation

void testDrive(int id, string makePref, string modelPref) {
  
  if (carLotPtr == nullptr)
    carLotPtr = new CarLot();

  for (int i = 0; i < carLotPtr->lotSize(); ++i) {
    Car *toBuy = carLotPtr->nextCar(); 
    
    cout << "Buyer " << id << endl;
    cout << "test driving " 
	 << toBuy->getMake() << " "
	 << toBuy->getModel();
    
    if (toBuy->getMake() == makePref && toBuy->getModel() == modelPref) {
      cout << " love it! buying it!" << endl;
      carLotPtr->buyCar(toBuy);
      return; // customer found prefered car
    } else
      cout << " did not like it!" << endl;
  }
}

int main() {
  srand(time(nullptr));
  
  const int numBuyers = 10;
  for(int i=0; i < numBuyers; ++i) {
    string make = rand() % 2 == 0 ? "Toyota" : "Ford"; 
    string model = make == "Toyota" ? 
      Toyota::getModels()[rand() % 5] :
      Ford::getModels()[rand() % 4];
    testDrive(i, make, model);
  }
}
