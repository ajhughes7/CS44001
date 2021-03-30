// vector and list algorithms
// Andrew Hughes
// 02/08/2020

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);  

// printing a list out
void printRoster(const list<string>& roster); 

void printStudentCourses(vector <list<string>> studentCourses);

list<string> getStudentCourseList(string studentName, 
vector <list<string>> courseStudents);


int main(int argc, char* argv[]){

  if (argc <= 1){ 

    cout << "usage: " << argv[0] 
	 << " list of courses, dropouts last" 
	 << endl; exit(1);
  }

  // vector of courses of students
  vector <list<string>> courseStudents; 
  vector <list<string>> studentCourses;
  for(int i=1; i < argc-1; ++i){
    list<string> roster;
    readRoster(roster, argv[i]);  
    //    cout << "\n\n" << argv[i] << "\n";  
    //      printRoster(roster);
    courseStudents.push_back(move(roster)); 
  }

  // reading in dropouts
  list<string> dropouts; 
  readRoster(dropouts, argv[argc-1]); 
  // cout << "\n\n dropouts \n"; printRoster(dropouts);

  // master list of students
  list<string> allStudents;  
 
  for(auto& lst : courseStudents) 
    //    allStudents.splice(allStudents.end(), lst);
    // copy rather than moving out of lst
    allStudents.insert(allStudents.end(), lst.begin(), lst.end());

  //  cout << "\n\n all students unsorted \n"; 
  //  printRoster(allStudents);

  // sorting master list
  allStudents.sort();
  //  cout << "\n\n all students sorted \n"; 
  //  printRoster(allStudents);

  // eliminating duplicates
  allStudents.unique(); 
  //  cout << "\n\n all students, duplicates removed \n"; 
  //  printRoster(allStudents);

  // removing individual dropouts
  for (const auto& str : dropouts)  
    allStudents.remove(str);

  //  cout << "\n\n all students, dropouts removed \n"; 
  //  printRoster(allStudents);
  for (const auto& studentName : allStudents) {
    list<string> scList = getStudentCourseList(studentName, courseStudents);
    studentCourses.push_back(move(scList));
  }
  printStudentCourses(studentCourses);
}

// reading in a file of names into a list of strings
void readRoster(list<string>& roster, string fileName){
  ifstream course(fileName);    
  string first, last;
  while(course >> first >> last)
    roster.push_back(move(first + ' ' + last));
  course.close();
}

// printing a list out
void printRoster(const list<string>& roster){
  for(const auto& str : roster)
    cout << str << endl;
}
// All Students
// last name, first name:  courses enrolled
void printStudentCourses(vector <list<string>> studentCourses) {
  cout << "All Students" << endl;
  cout << "firstName lastName: courses enrolled" << endl;
  for(list<string>& studentCourseList : studentCourses) {
    list<string>::iterator it = studentCourseList.begin();
    cout << *it << ": ";
    ++it;
    for (; it != studentCourseList.end(); ++it) {
      cout << *it << " ";   
    }
    cout << endl;
  }
}

list<string> getStudentCourseList(string studentName, vector <list<string>> courseStudents) {
  list<string> studentCourseList;
  studentCourseList.push_back(studentName);
  for(vector<int>::size_type i=0; i < courseStudents.size(); ++i) {
    list<string> studentList = courseStudents[i];
    if (std::find(studentList.begin(), studentList.end(), studentName) 
	!= studentList.end())
      studentCourseList.push_back("CS" + std::to_string(i + 1));
  }
  return studentCourseList;
}
