//**********************************************************************************************
//*  Project    : 	AVL Trees with Optimized Insertion and Deletion                            *
//                  supported with various Traversal Features                                  *
//*  Author     :   https://github.com/akcgjc007                                               *
//*  Email-Id   :   akcgjc007@gmail.com                                                        *
//**********************************************************************************************

#ifndef _AVL_H
#define _AVL_H

#include <stdio.h>
#include <stdlib.h>

//Tree_Node for a single node of the tree
typedef struct Tree_Node
{
	int data;											 	//data for tree_node
	struct Tree_Node *Left_Child;	 	//pointer to left child
	struct Tree_Node *Right_Child; 	//pointer to right child
	int H;												 	//Storing Height
} Tree_Node;
Tree_Node *Root = NULL;

//Queue which will store addresses of Tree_Node pointers
typedef struct Queue
{
	struct Tree_Node **data; 				//Pointer to a Tree_Node
	struct Queue *next;			 				//Pointer to next Queue_Node
} Queue;
Queue *Front = NULL, *Rear = NULL;
void Enqueue(Tree_Node **); 			// Enqueue function will add addresses of type Tree_Node to Queue
Tree_Node **Dequeue();						//Dequeue will return double pointers of Tree_Node
void Empty_My_Queue();

void InOrder(Tree_Node *);				// In(LC) + Value + In(RC)
void PreOrder(Tree_Node *);				// Value + PrO(LC) + PrO(RC)
void PostOrder(Tree_Node *);			// PostO(LC) + PostO(RC) + Value
void LevelOrder(Tree_Node *); 		// Level Order need not to be confused with Height //Level by level not by height
void Graph(Tree_Node *t);					// Real Visualization using a tree on 2-D Screen

int InO_P(Tree_Node **); 					// Hybridized version for deleting also
int InO_S(Tree_Node **); 					// Hybridized version for deleting also

void Delete_My_Tree(Tree_Node *);
int RInsert(Tree_Node **, int);
int Balance_Factor(Tree_Node *); 	// | H(Left_Child) - H(Right_Child) |
int Height_Calc(Tree_Node *);		 	// Height calculator
int max(int, int);
int Rec_H(Tree_Node *);						 //Recursive height maintainer
int Rec_Delete(Tree_Node **, int); // Rec delete operation
int Search(Tree_Node *t, int num); // Search for a number

Tree_Node *h_fix(Tree_Node **);			 //Balancing Utility
Tree_Node *LL_Rotation(Tree_Node *); //Both nodes on left, for left heavy
Tree_Node *LR_Rotation(Tree_Node *); //for left heavy
Tree_Node *RR_Rotation(Tree_Node *); //Both nodes on right, for right heavy
Tree_Node *RL_Rotation(Tree_Node *); //for right heavy

#endif