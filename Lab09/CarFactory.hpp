// interface for abstract and concrete car factories
// Mikhail Nesterenko
// 7/16/2014

#include <string>
#include <array>

// abstract product
class Car{
public:
  std::string getMake() const {return make_;}
  std::string getModel() const {return model_;}
protected:
  std::string make_; // this car's make
  std::string model_; // this car's model
};

// two concrete products
class Ford : public Car{
public:
  Ford();
  static const std::array<std::string, 4> getModels(){
    return {{"Focus", "Mustang", "Explorer", "F-150"}};
  };
};

class Toyota : public Car{
public:
  Toyota();
  static const std::array<std::string, 5> getModels() {
    return  {{"Corolla", "Camry", "Prius", "4Runner", "Yaris"}};
  };  


  
};


// absract factory
class CarFactory {
public:
  CarFactory(std::string location, int numCarsInProduction):
    numCarsInProduction_(numCarsInProduction),
    location_(location){}


  Car* requestCar();
  int getNumCarsInProduction() const {return numCarsInProduction_;}
  std::string getLocation() const {return location_;}
  virtual ~CarFactory(){}
protected:
  virtual Car* makeCar() =0;

private:
  int numCarsInProduction_;
  std::string location_;
};

// two concrete factories
class FordFactory : public CarFactory {
public:
  FordFactory(std::string location="", int numCarsInProduction=0):
    CarFactory(location, numCarsInProduction){}
protected:
  Car* makeCar() override;
};

class ToyotaFactory : public CarFactory {
public:
  ToyotaFactory (std::string location="", 
		 int numCarsInProduction=0):
    CarFactory(location, numCarsInProduction){}
protected:
  Car* makeCar() override;
};
