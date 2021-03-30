// example opening file for appending
// Andrew Hughes
// 03/21/2020

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>    

using std::cout; using std::endl; using std::string;


class Logger {
public:
  static Logger& instance() {
    static Logger logger;
    return logger;
  }

  void report(const string &s) {
    Logger::fout_ << s << endl;
  }

private:
  Logger();
  Logger(const Logger&) = delete;
  Logger & operator=(const Logger&) = delete;

  static void cleanUp();
  std::ofstream fout_;

};

Logger::Logger() {
  fout_.open("log.txt", std::fstream::out | std::fstream::app);
  atexit(cleanUp);
}

void Logger::cleanUp() {
  Logger::instance().fout_.close();
  cout << "Cleaned up" << endl;
}

void f1() {
  Logger::instance().report("f1 reporting");  
}

void f2() {
  Logger::instance().report("f2 reporting");  
}

int main() {
  f1();
  f2();
}

