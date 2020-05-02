//Author: Jason Yuan
//Implementation file of the puzzle class

#include "Puzzle.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <chrono>

//Constructor will initiate the first state of the Node
Puzzle::Puzzle(int* puzzle0)
{
   OpenNode = new Node;
   ClosedNode = new Node;

   OpenNode->link = 0;
   ClosedNode->link = 0;
   
   for(int i = 0; i < 9; i++)
   {
      OpenNode->matrix[i] = puzzle0[i];
      initPuzzle[i] = puzzle0[i];
   }

   //The initial puzzle display
   std::cout << "[InitialState] of the puzzle:" << std::endl;
   std::cout << OpenNode->matrix[1] << "  " << OpenNode->matrix[2] << "  " << OpenNode->matrix[3] << std::endl;
   std::cout << OpenNode->matrix[8] << "  " << OpenNode->matrix[0] << "  " << OpenNode->matrix[4] << std::endl;
   std::cout << OpenNode->matrix[7] << "  " << OpenNode->matrix[6] << "  " << OpenNode->matrix[5] << std::endl;
   std::cout << std::endl;

   PuzzleSolver();
}

//Function IsFinalState will tell if the Node matrix is the final state
bool Puzzle::IsFinalState()
{
   for(int i = 0; i < SIZE; i++)
   {
      if(OpenNode->matrix[i] != i) return false;
   }

   return true;
}

//Function IsReapted will check if the successor generated is repeated
bool Puzzle::IsRepeated(struct Node *testNode)
{
   int count = 0;

   if(ClosedNode == 0 && OpenNode == 0)
   {
      return false;
   }

   Node* cursor = ClosedNode;

   while(cursor != 0)
   {
      count = 0;

      for(int i = 0; i < SIZE; i++)
      {
	 if(cursor->matrix[i] != testNode->matrix[i])
            break;

	 count++;
      }

      if(count == 9) return true;
	 
      cursor = cursor->link;
   }

   cursor = OpenNode;

   while(cursor != 0)
   {
      count = 0;

      for(int i = 0; i < SIZE; i++)
      {
	 if(cursor->matrix[i] != testNode->matrix[i])
            break;

	 count++;
      }

      if(count == 9) return true;
	 
      cursor = cursor->link;
   }

   return false;
}

void Puzzle::ClearLinkedList()
{
   Node* tempNode = 0;

   while(OpenNode != 0)
   {
      tempNode = OpenNode;
      delete tempNode;
      OpenNode = OpenNode->link; 
   }

   while(ClosedNode != 0)
   {
      tempNode = ClosedNode;
      delete tempNode;
      ClosedNode = ClosedNode->link;
   }

   tempNode = 0;
   OpenNode = 0;
   ClosedNode = 0;

   std::cout << "Dynamic Memory Cleaned out! " << std::endl;
   std::cout << std::endl;
}

//heuristic function calculates h1 value
int Puzzle::H1Value(struct Node *node)
{
   int misPlaced = 0;
   
   for(int i = 0; i < SIZE; i++)
   {
       if(node->matrix[i] != i)
	 misPlaced++;
   }
   return misPlaced;
}

//heuristic function calculates h2 value
int Puzzle::H2Value(struct Node *node)
{
   int misDis = 0;

   for(int i = 0; i < SIZE; i++)
   {
      //When position is at 0
      if(i == 0)
      {
	 if(node->matrix[i] != 0 && node->matrix[i] % 2 == 0)
	   misDis += 1;

	 else if(node->matrix[i] % 2 == 1)
           misDis += 2;
      }

      //When position is at odd
      else if(i % 2 == 1)
      {
	 //when the odd number is at the odd postion
	 if(node->matrix[i] % 2 == 1 && node->matrix[i] != i)
	 {
	    if(std::abs(node->matrix[i] - i) == 6)
	      misDis += 2;

	    else 
	      misDis += std::abs(node->matrix[i] - i);
	 }

	 //when the even number is at the odd position
	 else if(node->matrix[i] != 0 && node->matrix[i] % 2 == 0)
	 {
	    if(std::abs(node->matrix[i] - i) == 7)
	       misDis += 1;
	 
	    else if(std::abs(node->matrix[i] - i) == 5)
               misDis += 3;
        
            else
               misDis += std::abs(node->matrix[i] - i);		    
	 }

	 //when zero is at the odd position
	 else if(node->matrix[i] == 0)
	   misDis += 2;
      }
   
      //when position is at even
      else if(i != 0 && i % 2 == 0)
      {
	  //when the odd number is at the even position
	  if(node->matrix[i] % 2 == 1)
	  {
	     if(std::abs(node->matrix[i] - i) == 7)
                misDis += 1;

             else if(std::abs(node->matrix[i] - i) == 5)
		misDis += 3;

	     else
		misDis += std::abs(node->matrix[i] - i);
	  }

	  //when the even number is at the even position
	  else if(node->matrix[i] != 0 && node->matrix[i] % 2 == 0 && node->matrix[i] != i)
	     misDis += 2;

	  //when zero is at the even position
	  else if(node->matrix[i] == 0)
	     misDis += 1;
      }
   }

   return misDis;
}

//function provide the coordinates system for the manhattan function
void Puzzle::Coordinates(int& x, int& y, int i)
{
   if(i == 0)
   {
      x = 2;
      y = 2;
   }

   else if(i == 1)
   {
      x = 1;
      y = 3;
   }
    
   else if(i == 2)
   {
      x = 2;
      y = 3;
   }

   else if(i == 3)
   {
      x = 3;
      y = 3;
   }

   else if(i == 4)
   {
      x = 3;
      y = 2;
   }

   else if(i == 5)
   {
      x = 3;
      y = 1;
   }

   else if(i == 6)
   {
      x = 2;
      y = 1;
   }

   else if(i == 7)
   {
      x = 1;
      y = 1;
   }
   
   else if(i == 8)
   {
      x = 1;
      y = 2;
   }
}

//heuristic function calculates Manhattan distance
int Puzzle::ManhattanDis(struct Node *node)
{
   int MHdis = 0,
       x1 = 0,
       y1 = 0,
       x2 = 0,
       y2 = 0;

   for(int i = 0; i < 9; i++)
   {
      if(node->matrix[i] != i)
      {
         this->Coordinates(x1,y1,i);
         this->Coordinates(x2,y2,node->matrix[i]);
         MHdis += std::abs(x1 - x2) + std::abs(y1 - y2);
      }
   }

   return MHdis;
}

//heuristic function calculates h3 value
int Puzzle::H3Value(struct Node *node)
{
   int outOfRow = 0;
   int outOfColumn = 0;

   for(int i = 0; i < SIZE; i++)
   {
      if(i == 1 || i == 2 || i == 3)
      {
	 if(node->matrix[i] != 1 && node->matrix[i] != 2 && node->matrix[i] != 3)
            outOfRow++;
      }

      else if(i == 8 || i == 0 || i == 4)
      {
	 if(node->matrix[i] != 8 && node->matrix[i] != 0 && node->matrix[i] != 4)
            outOfRow++;
      }

      else if(i == 7 || i == 6 || i == 5)
      {
	 if(node->matrix[i] != 7 && node->matrix[i] != 6 && node->matrix[i] != 5)
            outOfRow++;
      }

      else if(i == 1 || i == 8 || i == 7)
      {
	 if(node->matrix[i] != 1 && node->matrix[i] != 8 && node->matrix[i] != 7)
            outOfColumn++;
      }

      else if(i == 2 || i == 0 || i == 6)
      {
	 if(node->matrix[i] != 2 && node->matrix[i] != 0 && node->matrix[i] != 6)
            outOfRow++;
      }

      else if(i == 3 || i == 4 || i == 5)
      {
	 if(node->matrix[i] != 3 && node->matrix[i] != 4 && node->matrix[i] != 5)
            outOfRow++;
      }
   }

   return outOfRow + outOfColumn;
}

//Function InserNode will make the order of the Open LinkedList, and insert the new Node
void Puzzle::InsertNode(struct Node *inputNode)
{
   Node* cursor = OpenNode;
   Node* precursor = 0;

   /*std::cout << std::endl;
   std::cout << "this is the current Node insert to the Linked List:" << std::endl;
   std::cout << inputNode->matrix[1] << "  " << inputNode->matrix[2] << "  " << inputNode->matrix[3] << std::endl;
   std::cout << inputNode->matrix[8] << "  " << inputNode->matrix[0] << "  " << inputNode->matrix[4] << std::endl;
   std::cout << inputNode->matrix[7] << "  " << inputNode->matrix[6] << "  " << inputNode->matrix[5] << std::endl;
   std::cout << "h value is: " << inputNode->h << std::endl;
   std::cout << std::endl;*/
   
   if(OpenNode == 0)
   {
      OpenNode = inputNode;
      OpenNode->link = 0;
      inputNode = 0;
   }

   else if(OpenNode != 0)
   {
      while( cursor != 0 && inputNode->h > cursor->h)
      {
	  precursor = cursor;
	  cursor = cursor->link;
      }

      //Append a Node to the end of the OpenNode LinkedList
      if(cursor == 0)
      {
	 precursor->link = inputNode;
	 inputNode->link = 0;
	 inputNode = 0;
      }

      //Add a Node to the Head of the OpenNode LikedList
      else if(cursor == OpenNode)
      {
	 inputNode->link = OpenNode;
	 OpenNode = inputNode;
	 inputNode = 0;
      }

      else
      {
	 precursor->link = inputNode;
	 inputNode->link = cursor;
	 inputNode = 0;
      }
   }
}

//The function NextMove will decide where to move, and how many moves will happen
void Puzzle::NextMove(int FuncSelect)
{
   int spaceLoc = 0;
   Node* TempNode = 0;
   Node* tempNode = new Node;
   tempNode->link = 0;

   TempNode = OpenNode;
   *tempNode = *OpenNode;

   //Close the first Node in the OpenNode and Insert it to the ClosedNode
   OpenNode = OpenNode->link;
   TempNode->link = ClosedNode;
   ClosedNode = TempNode;
   TempNode = 0;
      
   //The Node to Expand
   std::cout << "Candidate next to be Expanded next:" << std::endl;
   std::cout << tempNode->matrix[1] << "  " << tempNode->matrix[2] << "  " << tempNode->matrix[3] << std::endl;
   std::cout << tempNode->matrix[8] << "  " << tempNode->matrix[0] << "  " << tempNode->matrix[4] << std::endl;
   std::cout << tempNode->matrix[7] << "  " << tempNode->matrix[6] << "  " << tempNode->matrix[5] << std::endl;
   std::cout << "h value is: " << tempNode->h << std::endl;
   std::cout << std::endl;

   //To find out the location of the space in the target matrix
   for(int i = 0; i < SIZE; i++)
   {
      if(tempNode->matrix[i] == 0)
      {
	 spaceLoc = i;
	 break;
      }
   }

   //when space is in the middle
   if(spaceLoc == 0)
   {
      Node* NodeUp = new Node;
      Node* NodeDown = new Node;
      Node* NodeLeft = new Node;
      Node* NodeRight = new Node;
      
      *NodeUp = *tempNode;
      *NodeDown = *tempNode;
      *NodeLeft = *tempNode;
      *NodeRight = *tempNode;
      
      //sapce move up
      if(NodeUp->matrix[2] != 2)
      {
         NodeUp->matrix[0] = tempNode->matrix[2];
         NodeUp->matrix[2] = tempNode->matrix[0];

         if(!this->IsRepeated(NodeUp))
         {
            if(FuncSelect == 1)
               NodeUp->h = this->H1Value(NodeUp);

	    else if(FuncSelect == 2)
	       NodeUp->h = this->H2Value(NodeUp);

	    else if(FuncSelect == 3)
	       NodeUp->h = this->ManhattanDis(NodeUp);

	    else if(FuncSelect == 4)
	       NodeUp->h = this->H3Value(NodeUp);

	    this->InsertNode(NodeUp);
         }
      }
      
      //space move down
      if(NodeDown->matrix[6] != 6)
      {
         NodeDown->matrix[0] = tempNode->matrix[6];
         NodeDown->matrix[6] = tempNode->matrix[0];

         if(!this->IsRepeated(NodeDown))
         {
	    if(FuncSelect == 1)
               NodeDown->h = this->H1Value(NodeDown);

	    else if(FuncSelect == 2)
	       NodeDown->h = this->H2Value(NodeDown);

	    else if(FuncSelect == 3)
	       NodeDown->h = this->ManhattanDis(NodeDown);

	    else if(FuncSelect == 4)
	       NodeDown->h = this->H3Value(NodeDown);
	    
	    this->InsertNode(NodeDown);
         }
      }

      //space move left
      if(NodeLeft->matrix[8] != 8)
      {
         NodeLeft->matrix[0] = tempNode->matrix[8];
         NodeLeft->matrix[8] = tempNode->matrix[0];

         if(!this->IsRepeated(NodeLeft))
         {
	    if(FuncSelect == 1)
               NodeLeft->h = this->H1Value(NodeLeft);

	    else if(FuncSelect == 2)
	       NodeLeft->h = this->H2Value(NodeLeft);

	    else if(FuncSelect == 3)
	       NodeLeft->h = this->ManhattanDis(NodeLeft);

	     else if(FuncSelect == 4)
	       NodeLeft->h = this->H3Value(NodeLeft);

	    this->InsertNode(NodeLeft);
         }
      }

      //space move right
      if(NodeRight->matrix[4] != 4)
      {
         NodeRight->matrix[0] = tempNode->matrix[4];
         NodeRight->matrix[4] = tempNode->matrix[0];
         
         if(!this->IsRepeated(NodeRight))
         {
	    if(FuncSelect == 1)
               NodeRight->h = this->H1Value(NodeRight);

	    else if(FuncSelect == 2)
	       NodeRight->h = this->H2Value(NodeRight);

	    else if(FuncSelect == 3)
	       NodeRight->h = this->ManhattanDis(NodeRight);

	     else if(FuncSelect == 4)
	       NodeRight->h = this->H3Value(NodeRight);

	    this->InsertNode(NodeRight);
         }
      }	 
   }

   //when the move is at odd position
   else if(spaceLoc % 2 == 1)
   {
      Node* NodeForward = new Node;
      Node* NodeBackward = new Node;

      *NodeForward = *tempNode;
      *NodeBackward = *tempNode;
    
      if(spaceLoc == 1)
      {
         if(NodeBackward->matrix[8] != 8)
	 {	      
            NodeBackward->matrix[1] = tempNode->matrix[8];
            NodeBackward->matrix[8] = tempNode->matrix[1];
            
            if(!this->IsRepeated(NodeBackward))
            {
	       if(FuncSelect == 1)
                  NodeBackward->h = this->H1Value(NodeBackward);

	       else if(FuncSelect == 2)
	          NodeBackward->h = this->H2Value(NodeBackward);

	       else if(FuncSelect == 3)
	          NodeBackward->h = this->ManhattanDis(NodeBackward);

	       else if(FuncSelect == 4)
	          NodeBackward->h = this->H3Value(NodeBackward);

	       this->InsertNode(NodeBackward);
            }
	 }	 
      }

      else
      {
	 if(NodeBackward->matrix[spaceLoc - 1] != spaceLoc - 1)
	 {
            NodeBackward->matrix[spaceLoc] = tempNode->matrix[spaceLoc - 1];
            NodeBackward->matrix[spaceLoc - 1] = tempNode->matrix[spaceLoc];
         
            if(!this->IsRepeated(NodeBackward))
            {
	       if(FuncSelect == 1)
                  NodeBackward->h = this->H1Value(NodeBackward);

	       else if(FuncSelect == 2)
	          NodeBackward->h = this->H2Value(NodeBackward);

	       else if(FuncSelect == 3)
	          NodeBackward->h = this->ManhattanDis(NodeBackward);

	        else if(FuncSelect == 4)
	          NodeBackward->h = this->H3Value(NodeBackward);

	       this->InsertNode(NodeBackward);
            }
         }
      }

      if(NodeForward->matrix[spaceLoc + 1] != spaceLoc + 1)
      {
         NodeForward->matrix[spaceLoc] = tempNode->matrix[spaceLoc + 1];
         NodeForward->matrix[spaceLoc + 1] = tempNode->matrix[spaceLoc];
         
         if(!this->IsRepeated(NodeForward))
         {
	    if(FuncSelect == 1)
               NodeForward->h = this->H1Value(NodeForward);

	    else if(FuncSelect == 2)
	       NodeForward->h = this->H2Value(NodeForward);
	     
	    else if(FuncSelect == 3)
	       NodeForward->h = this->ManhattanDis(NodeForward);

	    else if(FuncSelect == 4)
	       NodeForward->h = this->H3Value(NodeForward);

	    this->InsertNode(NodeForward);
         }
      }
   }

   //When the move is at even postion
   else if(spaceLoc != 0 && spaceLoc % 2 == 0)
   {
      Node* NodeForward = new Node;
      Node* NodeBackward = new Node;
      Node* NodeCenter = new Node;

      *NodeForward = *tempNode;
      *NodeBackward = *tempNode;
      *NodeCenter = *tempNode;
    
      if(spaceLoc == 8)
      {
         if(NodeForward->matrix[1] != 1)
	 {		 
            NodeForward->matrix[8] = tempNode->matrix[1];
            NodeForward->matrix[1] = tempNode->matrix[8];
            
            if(!this->IsRepeated(NodeForward))
            {
	       if(FuncSelect == 1)
                  NodeForward->h = this->H1Value(NodeForward);

	       else if(FuncSelect == 2)
	          NodeForward->h = this->H2Value(NodeForward);

	       else if(FuncSelect == 3)
	          NodeForward->h = this->ManhattanDis(NodeForward);

	       else if(FuncSelect == 4)
	          NodeForward->h = this->H3Value(NodeForward);

	       this->InsertNode(NodeForward);
            }              	 
         }
      }

      else
      {
	 if(NodeForward->matrix[spaceLoc + 1] != spaceLoc + 1)
	 {
            NodeForward->matrix[spaceLoc] = tempNode->matrix[spaceLoc + 1];
            NodeForward->matrix[spaceLoc + 1] = tempNode->matrix[spaceLoc];
            
            if(!this->IsRepeated(NodeForward))
            {
	       if(FuncSelect == 1)
                  NodeForward->h = this->H1Value(NodeForward);

	       else if(FuncSelect == 2)
	          NodeForward->h = this->H2Value(NodeForward);

	       else if(FuncSelect == 3)
	          NodeForward->h = this->ManhattanDis(NodeForward);

	       else if(FuncSelect == 4)
	          NodeForward->h = this->H3Value(NodeForward);

	       this->InsertNode(NodeForward);
            }
	 }
      }

      if(NodeBackward->matrix[spaceLoc - 1] != spaceLoc - 1)
      {
         NodeBackward->matrix[spaceLoc] = tempNode->matrix[spaceLoc - 1];
         NodeBackward->matrix[spaceLoc - 1] = tempNode->matrix[spaceLoc];
         
         if(!this->IsRepeated(NodeBackward))
         {
	    if(FuncSelect == 1)
               NodeBackward->h = this->H1Value(NodeBackward);

	    else if(FuncSelect == 2)
	       NodeBackward->h = this->H2Value(NodeBackward);

	    else if(FuncSelect == 3)
	       NodeBackward->h = this->ManhattanDis(NodeBackward);

	    else if(FuncSelect == 4)
	       NodeBackward->h = this->H3Value(NodeBackward);

	    this->InsertNode(NodeBackward);
         }
      }

      if(NodeCenter->matrix[0] != 0)
      {
         NodeCenter->matrix[spaceLoc] = tempNode->matrix[0];
         NodeCenter->matrix[0] = tempNode->matrix[spaceLoc];
       
         if(!this->IsRepeated(NodeCenter))
         {
	    if(FuncSelect == 1)
               NodeCenter->h = this->H1Value(NodeCenter);

	    else if(FuncSelect == 2)
	       NodeCenter->h = this->H2Value(NodeCenter);

	    else if(FuncSelect == 3)
	       NodeCenter->h = this->ManhattanDis(NodeCenter);

	    else if(FuncSelect == 4)
	       NodeCenter->h = this->H3Value(NodeCenter);

	    this->InsertNode(NodeCenter);
	 }
      }
   }
}

using namespace std::chrono;

void Puzzle::PuzzleSolver()
{
   int count = 0;
   int count2 = 0;
   int ng[4]; //number of Nodes generated
   int ne[4]; //number of Nodes expanded
   int d[4]; //depth of the tree
   float bStar[4]; //b* index
   int MO[4]; //memory used
   int tempH = 0;

   Node *cursor = 0;

   //solve the puzzle by using the heuristic function h1
   std::cout << "Soving Puzzle by using h1..." << std::endl;

   auto start = high_resolution_clock::now();
   while(!this->IsFinalState() && OpenNode != 0)
   {
      this->NextMove(1);
   }
   auto stop = high_resolution_clock::now();
   auto duration1 = duration_cast<microseconds>(stop - start);

   cursor = ClosedNode;
   while(cursor->link != 0)
   {
       cursor = cursor->link;
       count++;

       if(cursor->h > tempH)
       {
	 tempH = cursor->h;
	 count2++;
       }
   }

   ne[0] = count;
   d[0] = count2;

   cursor = OpenNode;
   while(cursor != 0)
   {
      cursor = cursor->link;
      count++;
   }

   ng[0] = count;
   bStar[0] = ng[0] / d[0];
   MO[0] = 48 * ng[0];

   std::cout << "[FinalState] by using h1:" << std::endl;
   std::cout << OpenNode->matrix[1] << "  " << OpenNode->matrix[2] << "  " << OpenNode->matrix[3] << std::endl;
   std::cout << OpenNode->matrix[8] << "  " << OpenNode->matrix[0] << "  " << OpenNode->matrix[4] << std::endl;
   std::cout << OpenNode->matrix[7] << "  " << OpenNode->matrix[6] << "  " << OpenNode->matrix[5] << std::endl;
   std::cout << "h value is: " << OpenNode->h << std::endl;
   std::cout << std::endl;

   std::cout << "Puzzle Solved by using h1" << std::endl;
   std::cout << "Execution time of h1 is: " << duration1.count() << " microseconds" << std::endl;
  
   this->ClearLinkedList();
   std::cout << "************************************************************************************" << std::endl;
   std::cout << std::endl;

   //get OpenNode and ClosedNode LinkedList ready, and copy the initial puzzle
   OpenNode = new Node;
   ClosedNode = new Node;
   OpenNode->link = 0;
   ClosedNode->link = 0;

   for(int i = 0; i < 9; i++)
      OpenNode->matrix[i] = initPuzzle[i];

   //solve the puzzle by using the heuristic function h2
   std::cout << "Soving Puzzle by using h2..." << std::endl;

   start = high_resolution_clock::now();
   while(!this->IsFinalState() && OpenNode != 0)
   {
      this->NextMove(2);
   }
   stop = high_resolution_clock::now();
   auto duration2 = duration_cast<microseconds>(stop - start);

   count = 0;
   count2 = 0;
   tempH = 0;
   cursor = ClosedNode;
   while(cursor->link != 0)
   {
       cursor = cursor->link;
       count++;

       if(cursor->h > tempH)
       {
	 tempH = cursor->h;
	 count2++;
       }
   }

   ne[1] = count;
   d[1] = count2;

   cursor = OpenNode;
   while(cursor != 0)
   {
      cursor = cursor->link;
      count++;
   }

   ng[1] = count;
   bStar[1] = ng[1] / d[1];
   MO[1] = 48 * ng[1];
   
   std::cout << "[FinalState] by using h2:" << std::endl;
   std::cout << OpenNode->matrix[1] << "  " << OpenNode->matrix[2] << "  " << OpenNode->matrix[3] << std::endl;
   std::cout << OpenNode->matrix[8] << "  " << OpenNode->matrix[0] << "  " << OpenNode->matrix[4] << std::endl;
   std::cout << OpenNode->matrix[7] << "  " << OpenNode->matrix[6] << "  " << OpenNode->matrix[5] << std::endl;
   std::cout << "h value is: " << OpenNode->h << std::endl;
   std::cout << std::endl;

   std::cout << "Puzzle Solved by using h2" << std::endl;
   std::cout << "Execution time of h2 is: " << duration2.count() << " microseconds" << std::endl;

   this->ClearLinkedList();
   std::cout << "************************************************************************************" << std::endl;
   std::cout << std::endl;

   //get OpenNode and ClosedNode LinkedList ready, and copy the initial puzzle
   OpenNode = new Node;
   ClosedNode = new Node;
   OpenNode->link = 0;
   ClosedNode->link = 0;

   for(int i = 0; i < 9; i++)
      OpenNode->matrix[i] = initPuzzle[i];

   //solve the puzzle by using the heuristic function Mahhatan Disatance
   std::cout << "Soving Puzzle by using Mahhatan Distance..." << std::endl;

   start = high_resolution_clock::now();
   while(!this->IsFinalState() && OpenNode != 0)
   {
      this->NextMove(3);
   }
   stop = high_resolution_clock::now();
   auto duration3 = duration_cast<microseconds>(stop - start);

   count = 0;
   count2 = 0;
   tempH = 0;
   cursor = ClosedNode;
   while(cursor->link != 0)
   {
       cursor = cursor->link;
       count++;

       if(cursor->h > tempH)
       {
	 tempH = cursor->h;
	 count2++;
       }
   }

   ne[2] = count;
   d[2] = count2;

   cursor = OpenNode;
   while(cursor != 0)
   {
      cursor = cursor->link;
      count++;
   }

   ng[2] = count;
   bStar[2] = ng[2] / d[2];
   MO[2] = 48 * ng[2];

   std::cout << "[FinalState] by using Manhattan Distance:" << std::endl;
   std::cout << OpenNode->matrix[1] << "  " << OpenNode->matrix[2] << "  " << OpenNode->matrix[3] << std::endl;
   std::cout << OpenNode->matrix[8] << "  " << OpenNode->matrix[0] << "  " << OpenNode->matrix[4] << std::endl;
   std::cout << OpenNode->matrix[7] << "  " << OpenNode->matrix[6] << "  " << OpenNode->matrix[5] << std::endl;
   std::cout << "h value is: " << OpenNode->h << std::endl;
   std::cout << std::endl;

   std::cout << "Puzzle Solved by using Manhattan Distance" << std::endl;
   std::cout << "Execution time of Mahhatan Distance is: " << duration3.count() << " microseconds" << std::endl;
  
   this->ClearLinkedList();
   std::cout << "************************************************************************************" << std::endl;
   std::cout << std::endl;

   //get OpenNode and ClosedNode LinkedList ready, and copy the initial puzzle 
   OpenNode = new Node;
   ClosedNode = new Node;
   OpenNode->link = 0;
   ClosedNode->link = 0;

   for(int i = 0; i < 9; i++)
      OpenNode->matrix[i] = initPuzzle[i];

   //solve the puzzle by using the heuristic function Mahhatan Disatance
   std::cout << "Soving Puzzle by using h3..." << std::endl;

   start = high_resolution_clock::now();
   while(!this->IsFinalState() && OpenNode != 0)
   {
      this->NextMove(4);
   }
   stop = high_resolution_clock::now();
   auto duration4 = duration_cast<microseconds>(stop - start);

   count = 0;
   count2 = 0;
   tempH = 0;
   cursor = ClosedNode;
   while(cursor->link != 0)
   {
       cursor = cursor->link;
       count++;

       if(cursor->h > tempH)
       {
	 tempH = cursor->h;
	 count2++;
       }
   }

   ne[3] = count;
   d[3] = count2;

   cursor = OpenNode;
   while(cursor != 0)
   {
      cursor = cursor->link;
      count++;
   }

   ng[3] = count;
   bStar[3] = ng[3] / d[3];
   MO[3] = 48 * ng[3];
   
   std::cout << "[FinalState] by using h3:" << std::endl;
   std::cout << OpenNode->matrix[1] << "  " << OpenNode->matrix[2] << "  " << OpenNode->matrix[3] << std::endl;
   std::cout << OpenNode->matrix[8] << "  " << OpenNode->matrix[0] << "  " << OpenNode->matrix[4] << std::endl;
   std::cout << OpenNode->matrix[7] << "  " << OpenNode->matrix[6] << "  " << OpenNode->matrix[5] << std::endl;
   std::cout << "h value is: " << OpenNode->h << std::endl;
   std::cout << std::endl;

   std::cout << "Puzzle Solved by using h3" << std::endl;
   std::cout << "Execution time of h3 is: " << duration4.count() << " microseconds" << std::endl;

   cursor = 0;
   this->ClearLinkedList();
   std::cout << "************************************************************************************" << std::endl;
   std::cout << std::endl;

   //Table Generated based on the Nodes
   std::cout << "Result Table:" << std::endl;
   std::cout << "Heuristic Function  | " << "ET(MicroSeconds), " << "NG, " << "NE, " << "d, " << "b*, " << "MO" << std::endl;
   std::cout << "       h1           | " << duration1.count() << ", " << ng[0] << ", " << ne[0] << ", " << d[0] << ", " << bStar[0] << ", " << MO[0] << std::endl;
   std::cout << "       h2           | " << duration2.count() << ", " << ng[1] << ", " << ne[1] << ", " << d[1] << ", " << bStar[1] << ", " << MO[1] << std::endl;
   std::cout << " Manhattan Distance | " << duration3.count() << ", " << ng[2] << ". " << ne[2] << ", " << d[2] << ", " << bStar[2] << ", " << MO[2] << std::endl;
   std::cout << "       h3           | " << duration4.count() << ", " << ng[3] << ", " << ne[3] << ", " << d[3] << ", " << bStar[3] << ", " << MO[3] << std::endl;
   std::cout << std::endl;
}
