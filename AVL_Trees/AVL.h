//**********************************************************************************************
//*  Project    : 	AVL Trees with Optimized Insertion and Ordered Traversal Support           *
//*  Author     :   Awesome@ANUPAM                                                             *
//*  Email-Id   :   akcgjc007@gmail.com                                                        *
//**********************************************************************************************

#include<stdio.h>
#include<stdlib.h>

//Tree_Node for a single node of the tree
typedef struct Tree_Node{
    int data;                       //data for tree_node
    struct Tree_Node* Left_Child;   //pointer to left child
    struct Tree_Node* Right_Child;  //pointer to right child
    int H;                          //Storing Height
}Tree_Node;
Tree_Node *Root=NULL;

//Queue which will store addresses of Tree_Node pointers
typedef  struct Queue{
    struct Tree_Node **data;        //Pointer to a Tree_Node
    struct Queue* next;            //Pointer to next Queue_Node
}Queue;
Queue *Front=NULL, *Rear=NULL;
void Enqueue(Tree_Node **);
Tree_Node** Dequeue();



void InOrder(Tree_Node*);
void PreOrder(Tree_Node*);
void PostOrder(Tree_Node*);
void LevelOrder(Tree_Node*);    //Level Order need not to be confused with Height

void Delete_My_Tree(Tree_Node*);
int RInsert(Tree_Node**t, int num);
int Balance_Factor(Tree_Node*);
int max(int, int);

Tree_Node* LL_Rotation(Tree_Node*a);        //Both nodes on left, for left heavy
Tree_Node* LR_Rotation(Tree_Node*t);        //for left heavy
Tree_Node* RR_Rotation(Tree_Node*a);        //Both nodes on right, for right heavy
Tree_Node* RL_Rotation(Tree_Node*a);        //for right heavy


int max(int a, int b)
{
    if( a > b) return a;
    else return b;
}

void InOrder(Tree_Node* x)
{
    if(x)
    {
        if(x->Left_Child)   InOrder(x->Left_Child);
        printf("<< %d..H is..%d >>\n", x->data, x->H);
        if(x->Right_Child)  InOrder(x->Right_Child);
    }
}
void PostOrder(Tree_Node* x)
{
    if(x)
    {
        if(x->Left_Child)   PostOrder(x->Left_Child);
        if(x->Right_Child)  PostOrder(x->Right_Child);
        printf("<< %d..H is..%d >>\n", x->data, x->H);
    }
}
void PreOrder(Tree_Node* x)
{
    if(x)
    {
        printf("<< %d..H is..%d >>\n", x->data, x->H);
        if(x->Left_Child)   PreOrder(x->Left_Child);
        if(x->Right_Child)  PreOrder(x->Right_Child);
    }
}
void Delete_My_Tree(Tree_Node* x)
{
    if(!x) return;
    Delete_My_Tree(x->Left_Child);
    Delete_My_Tree(x->Right_Child);
    free(x);
    Root = NULL;
}

int RInsert(Tree_Node** t ,int num)
{
    if(!Root)   //Root is null
    {
        Tree_Node *x;
        x = (Tree_Node*)malloc(sizeof(Tree_Node));
        x->data = num;
        x->Left_Child = x->Right_Child = NULL;
        x->H = 0;

        *t = x;
        return 0;
    }

    else if(*t)  //if t exists
    {
        if( num == (*t)->data )   //no need to insert
        {
            return (*t)->H;
        }
        else if( num > (*t)->data  )
        {
            int temp = RInsert(&(*t)->Right_Child, num);
            if( !(*t)->Left_Child ) //if left don't exist no need to compare
            {
                (*t)->H = 1 + temp;
                if( Balance_Factor(*t)==2 )
                {
                    if( (*t)->Right_Child )
                    {
                        if( (*t)->Right_Child->Right_Child )
                        {
                            *t = RR_Rotation(*t);
                        }
                        else
                        {
                            *t = RL_Rotation(*t);
                        }
                    }
                }
            }
            else
            {
                (*t)->H = 1 + max( (*t)->Left_Child->H, temp);  //it exist so finding the maximum of those
                if( Balance_Factor(*t)==2 )
                {
                    if( (*t)->Right_Child )
                    {
                        if( (*t)->Right_Child->Right_Child )
                        {
                            *t = RR_Rotation(*t);
                        }
                        else
                        {
                            *t = RL_Rotation(*t);
                        }
                    }
                }
            }
            return (*t)->H;
        }
        else if( num < (*t)->data )
        {
            int temp = RInsert(&(*t)->Left_Child, num);
            if( !(*t)->Right_Child )    //if right child doesn't exist
            {
                (*t)->H = 1 + temp;
                if( Balance_Factor(*t)==2 )
                {
                    if( (*t)->Left_Child )
                    {
                        if( (*t)->Left_Child->Left_Child )
                        {
                            *t = LL_Rotation(*t);
                        }
                        else
                        {
                            *t = LR_Rotation(*t);
                        }
                    }
                }
            }
            else                        //if right child exists
            {
                (*t)->H = 1 + max( temp, (*t)->Right_Child->H);
                if( Balance_Factor(*t)==2 )
                {
                    if( (*t)->Left_Child )
                    {
                        if( (*t)->Left_Child->Left_Child )
                        {
                            *t = LL_Rotation(*t);
                        }
                        else
                        {
                            *t = LR_Rotation(*t);
                        }
                    }
                }
            }
            return (*t)->H;
        }
    }
    else    //t doesn't exist
    {
        Tree_Node* x;
        x = (Tree_Node*)malloc(sizeof(Tree_Node));
        x->data = num;
        x->Left_Child = x->Right_Child = NULL;
        x->H = 0;
        *t = x;
        return 0;
    }
}

int Balance_Factor(Tree_Node* t)    //| H(Left_Child) - H(Right_Child) |
{
    if( !t )    return 0;

    int H_Left=-1, H_Right=-1;
    if( t->Left_Child )     H_Left = t->Left_Child->H;
    if( t->Right_Child )    H_Right = t->Right_Child->H;

    if( H_Left > H_Right )  return H_Left - H_Right;
    else                    return H_Right - H_Left;
}


Tree_Node* LL_Rotation(Tree_Node*a)
{
    Tree_Node *b;
    b = a->Left_Child;

    a->Left_Child  = b->Right_Child; //Mirroring of child from left to right
    b->Right_Child = a; //Now b become the root, or main Node

    a->H = b->Left_Child->H;
    b->H = a->H+1;

    return b;
}


Tree_Node* LR_Rotation(Tree_Node*t)
{
    Tree_Node* temp;
    temp = t->Left_Child->Right_Child;
    temp->Left_Child = t->Left_Child;
    temp->Right_Child = t;

    t->Left_Child->Right_Child = NULL;
    t->Left_Child = NULL;

    temp->H = 1;
    temp->Left_Child->H = 0;
    temp->Right_Child->H = 0;

    return temp;
}


Tree_Node* RR_Rotation(Tree_Node*a)
{
    Tree_Node *b;
    b = a->Right_Child;

    a->Right_Child  = b->Left_Child; //Mirroring of child from left to right
    b->Left_Child = a; //Now b become the root, or main Node

    a->H = b->Right_Child->H;
    b->H = a->H+1;

    return b;
}

Tree_Node* RL_Rotation(Tree_Node*t)
{
    Tree_Node* temp;
    temp = t->Right_Child->Left_Child;
    temp->Right_Child = t->Right_Child;
    temp->Left_Child = t;

    t->Right_Child->Left_Child = NULL;
    t->Right_Child = NULL;

    temp->H = t->H-1;
    temp->Right_Child->H--;
    temp->Left_Child->H = 0;

    return temp;
}
void Del_Node(int num)
{

}
void LevelOrder(Tree_Node* t)       //Level by level not by height
{
    Enqueue(&t);
    Tree_Node** x;
    while(Front)
    {
        x = Dequeue();
        printf(" < %d, h = %d > \n", (*x)->data, (*x)->H);
        if( (*x)->Left_Child )   Enqueue( &(*x)->Left_Child );
        if( (*x)->Right_Child )  Enqueue( &(*x)->Right_Child );
    }
}

void Enqueue( Tree_Node **data)     // Enqueue function will add addresses of type Tree_Node to Queue
{
    Queue* temp;
    temp = malloc(sizeof(Queue));
    temp->data = data;
    temp->next = NULL;

    if(Front==NULL){ Front = Rear = temp; }
    else
    {
        Rear->next = temp;
        Rear = temp;
    }
}

Tree_Node** Dequeue()       //Dequeue will return double pointers of Tree_Node
{
    if(Rear!=NULL)
    {
        if(!Front->next)
        {
            Tree_Node **p;
            p = Front->data;
            free(Front);
            Front=Rear=NULL;
            return p;
        }
        else
        {
            Tree_Node **p;
            Queue* q;
            q = Front;
            p = Front->data;
            Front = Front->next;
            free(q);
            return p;
        }
    }
    return NULL;
}
