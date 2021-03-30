// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Andrew Hughes
// 3/26/2020

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
  Fill(char fillChar, char bordChar):
    fillChar_(fillChar), bordChar_(bordChar){}
  
  virtual char getBorder()=0;
  virtual char getInternal()=0;
  virtual ~Fill() {}
protected:
  char fillChar_;
  char bordChar_;
};

// concrete body
class Hollow: public Fill{
public:
  Hollow(char bordChar):Fill(' ', bordChar){}
  char getBorder() override {return bordChar_;}
  char getInternal() override {return ' ';}
  ~Hollow(){}
};


// another concrete body
class Filled: public Fill {
public:
  Filled(char fillChar):Fill(fillChar, fillChar){}
  char getBorder() override {return fillChar_;}
  char getInternal() override {return fillChar_;}
  ~Filled(){}
};

class EnhancedFill: public Fill{
public:
  EnhancedFill(char fillChar, char bordChar):Fill(fillChar, bordChar){}
  char getBorder() override {return bordChar_;}
  char getInternal() override {return fillChar_;}
  ~EnhancedFill(){}
};

// abstract handle
class Figure {
public:
  Figure(int size, Fill* fill): size_(size), 
				fill_(fill){}
  virtual void draw() =0;
  virtual ~Figure(){}

  void changeFill(Fill* f) {
    fill_ = f;
  }

protected:
  int size_;
  Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
  Square(int size, Fill* fill): Figure(size, fill){}
  void draw() override;

};


void Square::draw(){
  for(int i=0; i < size_; ++i){
    for(int j=0; j < size_; ++j)
      if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	cout << fill_ -> getBorder();
      else
	cout << fill_ -> getInternal();
    cout << endl;
  }
}


int main(){
  // ask user for figure parameters
  cout << "Enter fill character: "; 
  char fchar; cin >> fchar;
  cout << "Enter border character: ";
  char bchar; cin >> bchar;
  cout << "Enter size: "; int size; cin >> size;

  Figure *userBox = new Square(size, new Filled(fchar));
  userBox->draw();
  cout << endl;

  userBox->changeFill(new Hollow(bchar));
  userBox->draw();
  cout << endl;

  userBox->changeFill(new EnhancedFill(fchar, bchar));
  userBox->draw();
  cout << endl;
}
