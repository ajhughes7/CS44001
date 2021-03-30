// demonstrates state design pattern
// Andrew Hughes
// 04/04/2020

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process{
public:
  Process();

  // behaviors
  void interrupt();
  void admit();
  void dispatch();
  void complete();
  void wait();
  void exit();

  Process* clone() {
    return new Process();}
  
  string report();

  // part of implementation of state pattern
  void changeState(State* s){state_=s;}
private:
  State* state_;
};

// absract state
class State{
public:
  // provides default implementation
  virtual void interrupt(Process*){} 
  virtual void admit(Process*){}  
  virtual void dispatch(Process*){} 
  virtual void complete(Process*){} 
  virtual void wait(Process*){} 
  virtual void exit(Process*){} 

  virtual string report() =0;
  void changeState(Process* c, State* s){
    c->changeState(s);
  }
};

class New: public State{
public:
  static State* instance(){
    static State* onlyInstance = new New;
    return onlyInstance;
  }
  void admit(Process*) override;  

  string report() override {return "New";}
private:
  New() {};
  New(const New&) = delete;
  New & operator=(const New&) = delete;
};

class Ready: public State{
public:
  static State* instance(){
    static State* onlyInstance = new Ready;
    return onlyInstance;
  }
  void dispatch(Process*) override;

  string report() override {return "Ready";}
private:
  Ready() {}
  Ready(const Ready&) = delete;
  Ready& operator=(const Ready&) = delete;
};


class Waiting: public State{
public:
  static State* instance(){
    static State* onlyInstance = new Waiting;
    return onlyInstance;
  }
  void complete(Process*) override;

  string report() override {return "Waiting";}
private:
  Waiting() {};
  Waiting(const Waiting&) = delete;
  Waiting& operator=(const Waiting&) = delete;
};

class Running: public State{
public:
  static State* instance(){
    static State* onlyInstance = new Running;
    return onlyInstance;
  }
  void interrupt(Process*) override;
  void exit(Process*) override;
  void wait(Process*) override;
  string report() override {return "Running";}
private:
  Running() {};
  Running(const Waiting&) = delete;
  Running& operator=(const Waiting&) = delete;
};

class Terminated: public State{
public:
  static State* instance(){
    static State* onlyInstance = new Terminated;
    return onlyInstance;
  }
  string report() override {return "Terminated";}
private:
  Terminated() {};
  Terminated(const Terminated&) = delete;
  Terminated& operator=(const Terminated&) = delete;
};

// state transitions member functions
// New
void Running::interrupt(Process *c) {
  changeState(c, Ready::instance());
} 

void New::admit(Process *c) {
  changeState(c, Ready::instance());
} 

void Ready::dispatch(Process *c) {
  changeState(c, Running::instance());
}

void Waiting::complete(Process *c) {
  changeState(c, Ready::instance());
}

void Running::wait(Process *c) {
  changeState(c, Waiting::instance());
} 


void Running::exit(Process *c) {
  changeState(c, Terminated::instance());
}

// Process member functions
Process::Process(){state_=New::instance();}

// handles/behaviors
void Process::interrupt(){state_->interrupt(this);}
void Process::admit(){state_->admit(this);}
void Process::dispatch(){state_->dispatch(this);}
void Process::complete(){state_->complete(this);}
void Process::wait(){state_->wait(this);}
void Process::exit(){state_->exit(this);}

string Process::report(){return state_->report();}

void demoStateTransitions() {
  Process process0;

  while(process0.report() != "Terminated"){
    cout << "What would you like Process0 to do? interrupt, admit, dispatch, complete, wait, or exit [i/a/d/c/w/e] ";
    char action; 
    cin >> action;
    
    switch (action) {
    case 'i':
      process0.interrupt();
      break;      
    case 'a':
      process0.admit();
      break;      
    case 'd':
      process0.dispatch();
      break;
    case 'c':
      process0.complete();
      break;      
    case 'w':
      process0.wait();
      break;      
    case 'e':
      process0.exit();
      break;      
    default:
      cout << "invalid entry: " << action << endl;
    }
    cout << "Process0 is " << process0.report() << endl;
  }

  // demonstrates that two Processs 
  // may be in two different states
  Process process1;
  cout << "Process0 " << process0.report() << " while "
       << "Process1 " << process1.report() << endl;
}

void demoPrototypeScheduler() {
  Process p;
  std::queue<Process*> q;

  for (int i = 0; i < 4; ++i)
    q.push(p.clone());

  srand(time(nullptr));

  while(!q.empty()) {
    Process* frontP = q.front();
    frontP->changeState(Running::instance());
    int action = rand() % 3;
    switch(action) {
    case 0:
      frontP->exit();
      break;
    case 1:
      frontP->interrupt();
      q.push(frontP);
      break;
    case 2:
      frontP->wait();
      cout << "Process: " << frontP->report() << endl;
      frontP->complete();
      q.push(frontP);
      break;
    }
    cout << "Process: " << frontP->report() << endl;
    q.pop();
  }
}

int main(){
  demoStateTransitions();
  demoPrototypeScheduler();
}
