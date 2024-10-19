#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class player
{
protected:
  const bool defect = 0;
  const bool coop = 1;
  bool choice;

public:
  player(){}
  virtual bool makeMove(int round = 0) = 0;
  virtual void strategy(bool opponentMove) = 0;
};


// ALWAYS COOPERATE
// Always cooperates.

class alwaysCoop : public player
{
public:
  alwaysCoop() {}
  ~alwaysCoop() {}

  bool makeMove(int round = 0)
  {  
    return coop;
  } 

  void strategy(bool opponentMove)
  {
    return;
  }

  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};


// ALWAYS DEFECT
// Always defects.

class alwaysDefect : public player
{
public:
  alwaysDefect() {}
  ~alwaysDefect() {}

  bool makeMove(int round = 0)
  {
    return defect;
  }

  void strategy(bool opponentMove)
  {
    return;
  }
  
  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};


// ALTERNATING
// Cooperates, then defects, then cooperates, then defects, then cooperates, etc.

class alternating : public player
{
public:
  alternating() {}
  ~alternating() {}

  bool makeMove(int round = 0)
  {
    if(round % 2 == 0)
    {
      return coop;
    }
    else
    {
      return defect;
    }
  }

  void strategy(bool opponentMove)
  {
    return;
  }
  
  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};


// HUNDRED HUNDRED
// Cooperates for the first hundred rounds; then, for the second hundred, defects.

class hundredHundred : public player
{
public:
  hundredHundred() {}
  ~hundredHundred() {}

  bool makeMove(int round = 0)
  {
    if(round < 100)
    {
      return coop; 
    }
    return defect;
  }

  void strategy(bool opponentMove)
  {
    return;
  }
  
  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};


// TIT FOR TAT
// Starts by cooperating; then, copies the last move its opponent played.

class titForTat : public player
{
private:
  bool opponent_previous_move;
public:
  titForTat(){}
  ~titForTat(){}

  bool makeMove(int round = 0)
  {
    static int i = 0;
    if(i == 0)
    {
      i++;
      return coop;
    }
    return opponent_previous_move;  
  }

  void strategy(bool opponentMove)
  {
    opponent_previous_move = opponentMove;
  }
  
  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};


// FRIEDMAN
// Starts by cooperating; then, after its opponent defects, defects for the rest of the game.
class friedman : public player
{
private:
  bool opponentDefects;
public:
  friedman()
  {
    opponentDefects = false;
  }
  ~friedman(){}

  bool makeMove(int round = 0)
  {
    if(opponentDefects)
    {
      return defect;
    }
    return coop;
  }

  void strategy(bool opponentMove)
  {
    if(opponentMove == defect)
    {
      opponentDefects = true;
    }
  }
  
  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};

// REVERSE TIT FOR TAT 
// Starts by defecting, then does the opposite of the opponent's last move.

class reverseTitForTat : public player
{
private:
  bool opponent_previous_move;
  bool move;
public:
  reverseTitForTat(){}
  ~reverseTitForTat(){}

  bool makeMove(int round = 0)
  {
    static int i = 0;
    if(i == 0)
    {
      i++;
      return defect;
    }
    return move;
  }

  void strategy(bool opponentMove)
  {
    switch(static_cast<int>(opponentMove))
    {
      case 1: move = 0;
        break;
      case 0: move = 1;
        break; 
    }
  }
  
  bool getChoice()
  {
    return choice;
  }

  void setChoice(bool choice)
  {
    this->choice = choice;
  }
};