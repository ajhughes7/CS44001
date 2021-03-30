// Lab 1: Diff: Compares strings from two seperate txt files 
// and outputs a carrot beneath the first character that differs. 
// Andrew Hughes
// 1/17/2020

/* prompt% diff file1.txt file2.txt

file1.txt: 20: Hello
file2.txt: 20: Hallo
                ^
file1.txt: 25: World????
file2.txt: 25: World!
                    ^
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using std::cout; using std::endl; using std::string; using std::setw;

int PAD_WIDTH = 2; // used format line number field output

// Returns index of first char that differs between s1 and s2, 
// or returns -1 if s1 == s2
int firstDiffIndex(string s1, string s2) {
  int i = 0;
  int s1Length = s1.length();
  int s2Length = s2.length();

  while (i < s1Length && i < s2Length && s1[i] == s2[i]) 
    ++i;
  return (s1Length == s2Length && i == s1Length ? -1 : i);  
}

// Outputs the following example: 
//     file1.txt: 20: Hello
//     file2.txt: 20: Hallo
//                     ^
void outputDiff(string fn1, string fn2, int lineNum, string line1, string line2) {
  int diffIndex = firstDiffIndex(line1, line2); 
  if (diffIndex == -1) 
    return;
  cout << fn1 << ": " << setw(PAD_WIDTH) << lineNum << ": " << line1 << endl;
  cout << fn2 << ": " << setw(PAD_WIDTH) << lineNum << ": " << line2 << endl;
  int leadingSpaceCount = fn2.length(); // assuming fn1 and fn2 same length
  leadingSpaceCount += 2; // ": "
  leadingSpaceCount += PAD_WIDTH;
  leadingSpaceCount += 2; // ": "
  leadingSpaceCount += diffIndex;
  string spaceString(leadingSpaceCount, ' ');
  cout << spaceString << '^' << endl;
}

int main(int argc, char* argv[]){
  if (argc == 3) {
    string fn1 = argv[1], fn2 = argv[2]; 
    std::ifstream file1(fn1);
    std::ifstream file2(fn2);
    std::string line1;
    std::string line2;
    int lineNum = 1; 
    
    while (getline(file1, line1)) {
      if (getline(file2, line2))
	outputDiff(fn1, fn2, lineNum, line1, line2);
      else 
	outputDiff(fn1, fn2, lineNum, line1, "");
      ++lineNum;
    }
    while (getline(file2, line2)) {
      outputDiff(fn1, fn2, lineNum, "", line2);
      ++lineNum;
    }
  } else {
    cout << "usage: diff file1 file2" << endl;
  }
}
