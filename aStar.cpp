//Author: Jason Yuan

#include <iostream>
#include "Puzzle.h"

using namespace std;

int main()
{
   //Main interface of the program to interact with the user
   const int SIZE = 9;
   char choice;
   bool end = false;

   int puzzle1 [SIZE] = {6, 2, 8, 3, 4, 5, 7, 0, 1}; //Inite state of puzzle #1
   int puzzle2 [SIZE] = {0, 2, 1, 6, 8, 3, 5, 7, 4}; //Inite state of puzzle #2

   cout << "Initial state of the puzzle #1:" << endl;
   cout << puzzle1[1] << "  " << puzzle1[2] << "  " << puzzle1[3] << endl;
   cout << puzzle1[8] << "  " << puzzle1[0] << "  " << puzzle1[4] << endl;
   cout << puzzle1[7] << "  " << puzzle1[6] << "  " << puzzle1[5] << endl;

   cout << endl;

   cout << "Initial state of the puzzle #2:" << endl;
   cout << puzzle2[1] << "  " << puzzle2[2] << "  " << puzzle2[3] << endl;
   cout << puzzle2[8] << "  " << puzzle2[0] << "  " << puzzle2[4] << endl;
   cout << puzzle2[7] << "  " << puzzle2[6] << "  " << puzzle2[5] << endl;

   cout << endl;

   while(!end)
   {
      cout << "Please enter the option to choose the puzzle:" << endl;
      cout << "A. puzzle #1" << endl;
      cout << "B. puzzle #2" << endl;
      cout << "C. quit the program!" << endl;

      cin >> choice;

      if(choice == 'a' || choice == 'A')
      {
          cout << "Option is A" << endl;
	  cout << endl;

	  Puzzle Puzzle1(puzzle1);
      }

      else if(choice == 'b' || choice == 'B')
      {
          cout << "Option is B" << endl;
	  cout << endl;

	  Puzzle Puzzle2(puzzle2);	 
      }
      
      else if(choice == 'c' || choice == 'C')
      {
	  cout << "Option is C" << endl;
	  cout << "shut down the program! Bye!" << endl;
	  end = true;
      }

      else
      {
	  cout << "ERROR! Invalid Input, Please Choose again!" << endl;
      }

   }

      return 0;  
}
