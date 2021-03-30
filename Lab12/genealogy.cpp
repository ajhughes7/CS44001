// traversing genealogical tree using Composite and Visitors
// Andrew Hughes
// 04/20/2020

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout; using std::cin; using std::endl;
using std::string; 
using std::vector;


class Person{ // component
public:
  Person(string firstName, Person *spouse, Person *father, Person *mother):
    firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
  const string & getFirstName(){return firstName_;}
  Person *getSpouse(){return spouse_;}
  void setSpouse(Person *spouse){spouse_=spouse;}
  Person *getFather(){return father_;}
  Person *getMother(){return mother_;}
  virtual void accept(class PersonVisitor *)=0;  
  virtual ~Person(){}
  bool legalMarriage(Person*);
  bool isSibling(Person*);
  bool isParent(Person*);
  bool isChild(Person*);
  bool isUncAunt(Person*);
  bool isAlreadyMarried(Person* p);
private:
  const string firstName_;
  Person *spouse_;
  Person *father_;
  Person *mother_;
};

bool Person::legalMarriage(Person* p) {
  if (this == p) {
    cout << "because self, ";
    return false;
  }
  if (isSibling(p)) {
    cout << "because sibling, ";
    return false;
  }
  if (isParent(p)) {
    cout << "becuase parent, ";
    return false;
  }
  if (isChild(p)) {
    cout << "because child, ";
    return false;
  }
  if (isUncAunt(p)) {
    cout << "because uncle or aunt, ";
    return false;
  }
  if (isAlreadyMarried(p)) {
    cout << "because married, ";
    return false;
  }
  return true;
}

class Woman;

bool Person::isSibling(Person* p) {
  return (getFather() == p->getFather() && getMother() == p->getMother());
  /*
  Person *mother = getMother();
  if (mother != nullptr)
    return false;
  //  Woman *m = static_cast<Woman *>(mother);
  //  vector<Person*> kids = m->getChildren();
  //  return std::count(kids.begin(), kids.end(), p);
  return false;
  */
}

bool Person::isParent(Person* p) {
  return (p == getMother() || p == getFather());
}

bool Person::isChild(Person* p) {
  return (p->getMother() == this || p->getFather() == this);
}
bool Person::isUncAunt(Person* p) {
  Person *m1 = getMother();
  Person *m2 = p->getMother();
  if (m1 == nullptr || m2 == nullptr)
    return false;
  return (isSibling(m2) || p->isSibling(m1));
}

bool Person::isAlreadyMarried(Person* p) {
  bool b1 = (getSpouse() != nullptr);
  bool b2 = (p->getSpouse() != nullptr);
  return (b1 || b2);
}

// leaf
// man has a last name 
class Man: public Person{
public:
  Man(string lastName, string firstName, Person *spouse, 
      Person *father, Person *mother): 
    Person(firstName, spouse, father, mother),
    lastName_(lastName) {}
  const string & getLastName(){return lastName_;}
  void accept(class PersonVisitor *visitor) override;
private:
  const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
  Woman(vector<Person *> children, 
	string firstName, 
	Person *spouse, 
	Person *father, Person *mother): 
    Person(firstName, spouse, father, mother), 
    children_(children){}
  const vector<Person *> & getChildren() {
    return children_;}
  void setChildren(const vector<Person *> &children){
    children_ = children;}
  void accept(class PersonVisitor *visitor) override;
private:
  vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
  virtual void visit(Man*)=0;
  virtual void visit(Woman*)=0;
  virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
  visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor){ 
  // children traversal through mother only
  // father's children are not traversed so as not 
  // to traverse them twice: for mother and father

  visitor->visit(this);
  // traversing descendants
  for(auto child : children_) 
    child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
  void visit(Man *m) override {
    cout << m->getFirstName() << " " << 
      m->getLastName() << endl;
  }

  void visit(Woman *w) override {
    cout << w->getFirstName() << " ";
    if (w->getSpouse() != nullptr)
      cout << static_cast<Man *> (w->getSpouse())->getLastName();
    else if (w->getFather() != nullptr)
      cout << static_cast<Man *> (w->getFather())->getLastName();
    else
      cout << "Doe";
    cout << endl;
  }
};

class ChildrenPrinter: public PersonVisitor{
public:
  void visit(Man *m) override {
    cout << m->getFirstName() << ": ";
    Woman *spouse = static_cast<Woman *>(m->getSpouse());
    if(spouse != nullptr)
      printNames(spouse->getChildren());
    cout << 
      cout << endl;
  }
  void visit(Woman *w) override {
    cout << w->getFirstName() << ": ";
    printNames(w->getChildren());
    cout << endl;
  }
private:
  void printNames(const vector<Person *> &children){
    for(const auto c: children)
      cout << c->getFirstName() << ", ";
  }
};

class MaidenPrinter: public PersonVisitor{
public:
  void visit(Man *m) override {
    cout << m->getFirstName() << " " << 
      m->getLastName() << endl;
  }

  void visit(Woman *w) override {
    cout << w->getFirstName() << " ";
    if (w->getFather() != nullptr) 
      cout << static_cast<Man *>(w->getFather())->getLastName();
    else 
      cout << "Doe";
    cout << endl;
  }
};



// part 2

class PersonFinder: public PersonVisitor {
public:
  PersonFinder(string firstName, string lastName):
    firstName_(firstName),
    lastName_(lastName),
    found(nullptr) {}

  void visit(Man *m) override {
    if (m->getFirstName() == firstName_ && m->getLastName() == lastName_)
      found = m;
  }

  void visit(Woman *w) override {
    string tempLastName = "";
    if (w->getFirstName() == firstName_) {
      if (w->getSpouse() != nullptr)
	tempLastName = static_cast<Man*>(w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	tempLastName = static_cast<Man*>(w->getFather())->getLastName();
      else
	tempLastName = "Doe";
    }
    if (tempLastName == lastName_) {
      found = w;
    }
  }
  
  Person* getFound() {
    return found;
  }
 
private:
  const string firstName_;
  const string lastName_;
  Person *found;
};




// demonstrating the operation

void legalMarriage(string p1first, string p1last, 
		   string p2first, string p2last, Woman* ms) {
  cout << "Can " << p1first << " " << p1last << " marry " 
       << p2first << " " << p2last << "?" <<  endl; 

  PersonFinder* finderOne 
    = new PersonFinder(p1first, p1last);
  ms->accept(finderOne);
  Person* personOne = finderOne->getFound();
    
  PersonFinder* finderTwo 
    = new PersonFinder(p2first, p2last);
  ms->accept(finderTwo);
  Person* personTwo = finderTwo->getFound();
  
  if(personOne->legalMarriage(personTwo))
    cout << "They can marry" << endl;
  else 
    cout << "They can't marry" << endl;      
}


int main(){

  // setting up the genealogical tree      
  // the tree is as follows
  //    
  //
  //       James Smith  <--spouse-->   Mary 
  //	                                  |
  //	                                 children -------------------------
  //	                                  |              |                |
  //	                                  |              |                |
  //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
  //	                                  |
  //	                                 children------------
  //	                                  |                 |
  //                                     |                 |
  //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
  //	       |
  //	     children
  //	       |
  //          |
  //	     Susan


  // first generation
  Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
  Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
  ms->setSpouse(js); js->setSpouse(ms);

  // second generation
  Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
  Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
  ps->setSpouse(wj); wj->setSpouse(ps);

  vector<Person *> marysKids  = {ps,
				 new Man("Smith", "Robert", nullptr, js, ms),
				 new Woman({}, "Linda", nullptr, js, ms)};
  ms->setChildren(marysKids);

  // third generation
  Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
  vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
  ps->setChildren(patsKids);

  Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
  vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

  jj->setSpouse(mj); mj->setSpouse(jj);
  jj->setChildren(jensKids);
   

  // defining two visitors
  ChildrenPrinter *cp = new ChildrenPrinter;
  //NamePrinter *np = new NamePrinter;
  MaidenPrinter *mp = new MaidenPrinter;

  // executing the traversal with the composite
  // and the specific visitor

  cout << "\n MAIDEN NAME LIST\n";
  //   ms->accept(np);
  ms->accept(mp);

  cout << endl << endl;

  //  cout << "CHILDREN LIST\n";
  //  ms->accept(cp);
 
  // Can't marry oneself
  legalMarriage("Robert", "Smith", "Robert", "Smith", ms);

  // Can't marry one's children
  legalMarriage("Patricia", "Johnson", "Michael", "Johnson", ms);

  // Can't marry one's parents
  legalMarriage("Michael", "Johnson", "Patricia", "Johnson", ms);

  // Siblings can't marry
  legalMarriage("Robert", "Smith", "Patricia", "Johnson", ms);
  legalMarriage("Robert", "Smith", "Linda", "Smith", ms);

  // Can't marry if already married 
  legalMarriage("Michael", "Johnson", "Mary", "Smith", ms); 

  // Can't marry one's Uncle or Aunt
  legalMarriage("Robert", "Smith", "Michael", "Johnson", ms);
  legalMarriage("Michael", "Johnson", "Robert", "Smith", ms);


  cout << endl;

  while (true) {
    cout << "Enter two people to see if they're able to get married (firstName lastName)" << endl;
    string p1first, p1last, p2first, p2last;
    cout << "Enter first person: ";
    cin >> p1first;
    cin >> p1last; 

    cout << "Enter second person: "; 
    cin >> p2first;
    cin >> p2last;

    legalMarriage(p1first, p1last, p2first, p2last, ms);
  }
}
  



