#include "player.h"

const int coopCoop = 3;
const int defectDefect = 1;
const int coopDefect = 0;
const int defectCoop = 5;
const int COOP = 1;
const int DEFECT = 0;
const int NUM_ROUNDS = 200;
const int STRAT_NUM = 7;

// FUNCTION PROTOTYPES

void addPoints(bool p1_choice, bool p2_choice, int &p1_points, int &p2_points);
ostringstream resultScreen(int p1_points, int p2_points);
void show_options(vector<string> strat_list);
void setPlayerStrat(int strat_choice, player* &plyr);
void game(bool p1_choice, bool p2_choice, int &p1_points, int &p2_points, player* plyr1, player* plyr2);
char getUserInput();

int main()
{
// SET THE PLAYERS HERE //

  player* player1;
  player* player2;
  int p1_strat = 0;
  int p2_strat = 0;

  bool p1_choice;
  bool p2_choice;

  char cont_game = ' ';

  vector<string> strat_list = {"Always Cooperate", 
                               "Always Defect", 
                               "Alternating", 
                               "Hundred-Hundred", 
                               "Friedman", 
                               "Tit For Tat",
                               "Reverse Tit For Tat"};

  do // while(toupper(cont_game) == 'Y');
  {
    int p1_points = 0;
    int p2_points = 0;
    // get strategy one
    cout << "Choose Strategy 1:\n";
    show_options(strat_list);
    cout << endl << "Enter your strategy:  ";
    cin  >> p1_strat;

    // clear
    system("cls");

    // get strategy two
    cout << "Choose Strategy 2:\n";
    show_options(strat_list);
    cout << endl << "Enter your strategy:  ";
    cin >> p2_strat;
    cin.ignore();

    // clear
    system("cls");

    // set player 1 strategy
    setPlayerStrat(p1_strat, player1);

    // set player 2 strategy
    setPlayerStrat(p2_strat, player2);

    // start of the game
    game(p1_choice, p2_choice, p1_points, p2_points, player1, player2);

    cout << "\nRun another simulation? (Y/N):  ";
    cont_game = getUserInput();
    system("cls");

    // deletes what the player pointer is pointing to
    delete player1;
    delete player2;
    
  }while(toupper(cont_game) == 'Y');

  // ends the program
  return 0;
}

void addPoints(bool p1_choice, bool p2_choice, int &p1_points, int &p2_points)
{
  if(p1_choice == COOP && p2_choice == COOP)
  {
    p1_points += coopCoop;
    p2_points += coopCoop;
  }
  else if(p1_choice == COOP && p2_choice == DEFECT)
  {
    p1_points += coopDefect;
    p2_points += defectCoop;
  }
  else if(p1_choice == DEFECT && p2_choice == COOP)
  {
    p1_points += defectCoop;
    p2_points += coopDefect;
  }
  else if (p1_choice == DEFECT && p2_choice == DEFECT)
  {
    p1_points += defectDefect;
    p2_points += defectDefect;
  }
}

ostringstream resultScreen(int p1_points, int p2_points)
{
  ostringstream oss;
  
  oss << "\n\n*************************************************************\n"
      << "*          FINAL RESULTS OF THE PRISONER'S DILEMMA\n"
      << "*\n"
      << "*\n"
      << "* PLAYER 1:  " << p1_points << " POINTS\n"
      << "* PLAYER 2:  " << p2_points << " POINTS\n"       
      << "*\n"
      << "*"
      << "*"
      << "*************************************************************\n";

  return oss;
}

void game(bool p1_choice, bool p2_choice, int &p1_points, int &p2_points, player* plyr1, player* plyr2)
{
  // the players go for a set number rounds
  for(int i = 0; i < NUM_ROUNDS; i++)
  { 
    // player 1 makes their choice
    p1_choice = plyr1->makeMove(i);
    // player 2 makes their choice
    p2_choice = plyr2->makeMove(i);
    // strategies for each player being made
    plyr1->strategy(p2_choice);
    plyr2->strategy(p1_choice);

    // point accumulation
    addPoints(p1_choice, p2_choice, p1_points, p2_points);
  }

  // end of the game
  // RESULT SCREEN
  ostringstream screen = resultScreen(p1_points, p2_points);
  cout << screen.str();
}

void show_options(vector<string> strat_list)
{
  int option = 0;

  for(auto i : strat_list)
  {
    cout << "\nStrategy #" << option + 1 << ": " << strat_list[option];
    option++; 
  }
}

void setPlayerStrat(int strat_choice, player* &plyr)
{
  switch(strat_choice)
  {
    case 1: plyr = new alwaysCoop;
      break;
    case 2: plyr = new alwaysDefect;
      break;
    case 3: plyr = new alternating;
      break;
    case 4: plyr = new hundredHundred;
      break;
    case 5: plyr = new friedman;
      break;
    case 6: plyr = new titForTat;
      break;
    case 7: plyr = new reverseTitForTat;
      break;
  }
}

char getUserInput()
{ 
    char input;
    cin.get(input);
    input = toupper(input);
    return input;
}