//Author: Jason Yuan
//Header file of Puzzle class

#ifndef PUZZLE_H
#define PUZZLE_H

class Puzzle
{
public:
   struct Node
   {
      Node* link;
      int matrix[9];
      int h; //heruistic value
   };

   Node* OpenNode = 0;
   Node* ClosedNode = 0;

   const int SIZE = 9;
   int initPuzzle[9]; 
   
   Puzzle(int* puzzle);
   bool IsFinalState();
   bool IsRepeated(struct Node *testNode);

   void ClearLinkedList();
   int H1Value(struct Node *node);//heuristic function 1 
   int H2Value(struct Node *node);//heuristic function 2
   int H3Value(struct Node *node);//heuristic function 3
   void Coordinates(int& x, int& y, int i);
   int ManhattanDis(struct Node *node);//heuristic function 4
   void InsertNode(struct Node *inputNode);
   void NextMove(int FuncSelect);
   void PuzzleSolver();
};

#endif
