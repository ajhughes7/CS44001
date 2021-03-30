// Reads in a file and outputs words and their sorted counts
// Andrew Hughes
// 1/25/2020

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "WordList.hpp" 

using std::cout; using std::endl; using std::string; using std::fstream;

int main(int argc, char* argv[]){
  if (argc == 2) {    
    string fn = argv[1];
    char ch;
    fstream fin(fn, fstream::in);
    string word = "";
    WordList wl;
    while (fin >> std::noskipws >> ch) {
      if (isalnum(ch)) 
	word += ch;  // build word
      else if (word != "") {
        wl.addWord(word); // add completed word 
	word = "";
      }
    }
    cout << "word list:" << endl;
    wl.print();    
  } else {
    cout << "usage: wordcount file1" << endl;
  }
}

