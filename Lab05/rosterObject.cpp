// Roster with Class Schedule, implemented using map
// Andrew Hughes
// 2/14/2020

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::map;

class Student{
public:
  Student(string firstName, string lastName): 
    firstName_(firstName), lastName_(lastName) {}
 
  // move constructor, not really needed, generated automatically
  Student(Student && org):
    firstName_(move(org.firstName_)),
    lastName_(move(org.lastName_))
  {}
  
  // force generation of default copy constructor
  Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

  // needed for unique() and for remove()
  friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	left.firstName_ == right.firstName_;
  }

  // needed for sort()
  friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
			      (left.lastName_ == right.lastName_ && 
			       left.firstName_ < right.firstName_);
  }
private:
  string firstName_;
  string lastName_;
  list<string> courses_;
};

void addStudent(map<Student, list<string>> &studentToCourseList, 
		string fileName);

// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

void printStudentToCourseList(map<Student, list<string>> studentToCourseList);

string join(list<string>);

void delStudent (map<Student, list<string>> &studentToCourseList, 
		 string fileName);

int main(int argc, char* argv[]){

  if (argc <= 1){ cout << "usage: " << argv[0] 
		       << " list of courses, dropouts last" << endl; exit(1);}
  map<Student, list<string>> studentToCourseList; 
  for(int i=1; i < argc-1; ++i)
    addStudent(studentToCourseList, argv[i]);  
  delStudent(studentToCourseList, argv[argc-1]);
  printStudentToCourseList(studentToCourseList);
}
 
// reads in a file and adds students to studentToCourseList map
// for course given by fileName
void addStudent(map<Student, list<string>> &studentToCourseList, 
		string fileName){
  ifstream course(fileName);
  string first, last;
  while(course >> first >> last) {
    string courseName = fileName.substr(0, fileName.length() - 4);
    for (auto & c: courseName) 
      c = toupper(c);  
    studentToCourseList[Student(first, last)].push_back(courseName);
}
  course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
  cout << "All Students" << endl;
  cout << "firstName lastName: courses enrolled" << endl;
  for(const auto& student : roster)
    cout << student.print() << endl;
}

void printStudentToCourseList(map<Student, list<string>> studentToCourseList) {
  cout << "All Students" << endl;
  cout << "firstName lastName: courses enrolled" << endl;
  for (map<Student, list<string>>::iterator it = studentToCourseList.begin();        it != studentToCourseList.end(); ++it) {
    cout << it->first.print() << ": " << join(it->second) << endl;
  }
}

// https://stackoverflow.com/questions/15347123/how-to-construct-a-stdstring-from-a-stdvectorstring
// add seperator
string join(const list<string> l) {
  string s = "";
  for (const auto e: l) { 
    s += e + " ";
  }
  return s;
}
 
//delStudent() remove from map
void delStudent(map<Student, list<string>> &studentToCourseList, 
		string fileName) {
  ifstream course(fileName);
  string first, last;
  while(course >> first >> last) {
    string courseName = fileName.substr(0, fileName.length() - 4);
    studentToCourseList.erase(Student(first, last));
  }
  course.close();
}
