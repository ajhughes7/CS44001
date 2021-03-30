// Header file for WordOccurrence class 
// Andrew Hughes
// 1/25/2020

class WordOccurrence {
public:
  WordOccurrence(const std::string& word="", int num=0);
  bool matchWord(const std::string &); // returns true if word matches stored
  friend bool equal(const WordOccurrence&, const WordOccurrence&);
  friend bool operator<(WordOccurrence const&, WordOccurrence const&);
  void increment(); // increments number of occurrences
  std::string getWord() const; 
  int getNum() const;

private:
  std::string word_;
  int num_;
};
