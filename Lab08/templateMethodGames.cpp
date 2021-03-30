// Games, Template Method example
// Andrew Hughes
// 3/26/2020

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl; using std::cin; using std::string;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	 makeMove(i);
	 if (i==playersCount_-1) 
	    ++movesCount_; 
      }

      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 3; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

/*


class OldDice: public Game {
public:
  // implementing concrete methods
  void initializeGame() {
    playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
  }
  


  void fiveRolls(int total, int &maxTotal, string rolls, string highScore) {
    cout << rolls;
    for (int i = 0; i < 5; ++i) {
      int oneRoll = rand() % 6 + 1;
      total += oneRoll;
      cout << oneRoll << " ";
    }
    cout << "= " << total << ", " << highScore;
    
    if (total > maxTotal)
      maxTotal = total;
    cout << maxTotal << endl;
  }

  
  void makeMove(int player) {
    cout << endl;

    srand(time(nullptr));
    int computerRoll = 1;
    char rollAgain = 'y';
    
    for (int i = 0; i < 3; ++i) {
      int playerTotal = 0; 
      int computerTotal = 0;
      
      // computer roll 
      if (computerRoll == 1) {
	
	fiveRolls(computerTotal, maxComputerTotal, 
		  "Computer rolled: ", "computer's highest score ");
	computerRoll = rand() % 2;
      }	 else 
	cout << "Computer rolled: passed, computer's highest score = " 
	     << maxComputerTotal << endl;      
      
      // player roll
      if (rollAgain == 'y') {
	fiveRolls(playerTotal, maxPlayerTotal, 
		  "You rolled: ", "your highest score = ");
	cout << "Roll again? [y/n] ";
	cin >> rollAgain;
      } else 
	cout << "You rolled: passed, your highest score = " << maxPlayerTotal
	     << endl;      
      if (computerRoll != 1 && computerRoll != 'y' )
	break;
    } 
  }
  
  void printWinner() {
    if (maxPlayerTotal > maxComputerTotal) {
      cout << "you won" << endl;
      //      playerWon_ = player;
    } else 
      cout << "you lose" << endl;
  }

private: 
  static const int numPlayers_ = 2;
  static const int minMoves_ = 1; // nobody wins before minMoves_
  static const int maxMoves_ = 3; // somebody wins before maxMoves_
  int maxComputerTotal= 0;
  int maxPlayerTotal = 0; 

};

*/

class Dice: public Game {
  void initializeGame(){
    playersCount_ = numPlayers_;
  }
  void fiveRolls(int total, int &maxTotal, string rolls, string highScore) {
    cout << rolls;
    for (int i = 0; i < 5; ++i) {
      int oneRoll = rand() % 6 + 1;
      total += oneRoll;
      cout << oneRoll << " ";
    }
    cout << "= " << total << ", " << highScore;
    
    if (total > maxTotal)
      maxTotal = total;
    cout << maxTotal << endl;
  }

  void makeMove(int player){
    if (movesCount_ >= maxMoves_) {
      maxTurnsReached = true;    
      return;
    }
    
    if (player == USER && !userDone)
      fiveRolls(playerTotal, maxPlayerTotal, 
		"You rolled: ", "your highest score = ");
    else if (player == COMPUTER && !computerDone)
      fiveRolls(computerTotal, maxComputerTotal, 
		"Computer rolled: ", "computer's highest score ");
    if(movesCount_ < maxMoves_ - 1) {
      if (player == COMPUTER && !computerDone) {
	computerDone = rand() % 2;      
	if (computerDone)
	  cout << "Computer rolled: passed" << endl;
      }
      if (player == USER && !userDone) {
	cout << "Roll again? [y/n] ";            
	char rollAgain;
	cin >> rollAgain;
	userDone = rollAgain != 'y';
      }       
    }    
  }
  void printWinner() {
    if (maxPlayerTotal > maxComputerTotal) {
      cout << "you won" << endl;
    } else 
      cout << "you lose" << endl;
  }
  bool endOfGame() {
    return playerWon_ != noWinner
      || maxTurnsReached
      || (userDone && computerDone);
  }
  
private:
  bool maxTurnsReached = false;
  bool userDone = false;
  bool computerDone = false;
  static const int numPlayers_ = 2;
  static const int minMoves_ = 1; // nobody wins before minMoves_
  static const int maxMoves_ = 3; // somebody wins before maxMoves_
  const int COMPUTER = 0;
  const int USER = 1;
  int maxComputerTotal= 0;
  int maxPlayerTotal = 0; 
  int playerTotal = 0;
  int computerTotal = 0;
};



int main() {
   srand(time(nullptr));

   Game* gp = nullptr;
   /*
   // play chess 10 times
   for (int i = 0; i < 10; ++i){ 
      gp = new Chess;
      gp->playGame(); 
      delete gp;
   }
      

   // play monopoly 5 times
   for (int i = 0; i < 5; ++i){
      gp = new Monopoly;
      gp->playGame(); 
      delete gp;
   }
   */

   // play dice 
   gp = new Dice;
   gp->playGame();
   delete gp;
}
