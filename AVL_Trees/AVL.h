//**********************************************************************************************
//*  Project    : 	AVL Trees with Optimized Insertion and Deletion                            *
//                  supported with various Traversal Features                                  *
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
    struct Queue* next;             //Pointer to next Queue_Node
}Queue;
Queue *Front=NULL, *Rear=NULL;
void Enqueue(Tree_Node **);         // Enqueue function will add addresses of type Tree_Node to Queue
Tree_Node** Dequeue();              //Dequeue will return double pointers of Tree_Node
void Empty_My_Queue();



void InOrder(Tree_Node*);           // In(LC) + Value + In(RC)
void PreOrder(Tree_Node*);          // Value + PrO(LC) + PrO(RC)
void PostOrder(Tree_Node*);         // PostO(LC) + PostO(RC) + Value
void LevelOrder(Tree_Node*);        // Level Order need not to be confused with Height //Level by level not by height
void Graph(Tree_Node*t);            // Real Visualization using a tree on 2-D Screen

int InO_P(Tree_Node**);           // Hybridized version for deleting also
int InO_S(Tree_Node**);           // Hybridized version for deleting also

void Delete_My_Tree(Tree_Node*);
int RInsert(Tree_Node**, int);
int Balance_Factor(Tree_Node*);     // | H(Left_Child) - H(Right_Child) |
int Height_Calc(Tree_Node*);        // Height calculator
int max(int, int);
int Rec_H( Tree_Node* );                   //Recursive height maintainer
int Rec_Delete(Tree_Node**, int);     // Rec delete operation
int Search(Tree_Node*t, int num);                  // Search for a number

Tree_Node* h_fix(Tree_Node**);              //Balancing Utility
Tree_Node* LL_Rotation(Tree_Node*);        //Both nodes on left, for left heavy
Tree_Node* LR_Rotation(Tree_Node*);        //for left heavy
Tree_Node* RR_Rotation(Tree_Node*);        //Both nodes on right, for right heavy
Tree_Node* RL_Rotation(Tree_Node*);        //for right heavy

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

void LevelOrder( Tree_Node* t )
{
    if(!t) return;
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
                *t = h_fix(t);
            }
            else
            {
                (*t)->H = 1 + max( (*t)->Left_Child->H, temp);  //it exist so finding the maximum of those
                *t = h_fix(t);
            }
            return (*t)->H;

        }
        else if( num < (*t)->data )
        {
            int temp = RInsert(&(*t)->Left_Child, num);
            if( !(*t)->Right_Child )    //if right child doesn't exist
            {
                (*t)->H = 1 + temp;
                *t = h_fix(t);
            }
            else                        //if right child exists
            {
                (*t)->H = 1 + max( temp, (*t)->Right_Child->H);
                *t = h_fix(t);
            }
            return (*t)->H;
        }
    }
    else    //t doesn't exist, actual creation of node starts here, also Termination of Recursion
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

int Balance_Factor(Tree_Node* t)
{
    if( !t )    return 0;

    int H_Left=-1, H_Right=-1;
    if( t->Left_Child )     H_Left = t->Left_Child->H;
    if( t->Right_Child )    H_Right = t->Right_Child->H;

    if( H_Left > H_Right )  return H_Left - H_Right;
    else                    return H_Right - H_Left;
}




Tree_Node* h_fix(Tree_Node** t)
{
    if( Balance_Factor(*t) >= 2 )
    {
        if( Height_Calc((*t)->Left_Child) > Height_Calc((*t)->Right_Child)  )//L rotations
        {
            if( Height_Calc((*t)->Left_Child->Left_Child) > Height_Calc((*t)->Left_Child->Right_Child) )
            {
                return LL_Rotation(*t);
            }
            else
            {
                return LR_Rotation(*t);
            }
        }
        else // R rotations
        {
            if( Height_Calc((*t)->Right_Child->Left_Child) < Height_Calc((*t)->Right_Child->Right_Child) )
            {
                return RR_Rotation(*t);
            }
            else
            {
                return RL_Rotation(*t);
            }
        }
    }
    else
    {
        return *t;
    }
}

Tree_Node* LL_Rotation(Tree_Node*t)
{
    Tree_Node *x = t->Left_Child;

    t->Left_Child  = x->Right_Child; //Mirroring of child from left to right
    x->Right_Child = t; //Now b become the root, or main Node

    t->H = 1 + max(Height_Calc(t->Right_Child), Height_Calc(t->Left_Child));
    x->H = 1 + max( x->Left_Child->H, x->Right_Child->H );

    return x;
}

Tree_Node* LR_Rotation(Tree_Node*t)
{
    Tree_Node*p = t->Left_Child;
    Tree_Node *x = t->Left_Child->Right_Child;
    t->Left_Child->Right_Child = x->Left_Child;
    t->Left_Child = x->Right_Child;

    x->Left_Child = p;
    x->Right_Child = t;

    p->H = 1 + max( Height_Calc(p->Left_Child), Height_Calc(p->Right_Child) );
    t->H = 1 + max( Height_Calc(t->Left_Child), Height_Calc(t->Right_Child) );
    x->H = 1 + max( p->H, t->H );


    return x;
}

Tree_Node* RR_Rotation(Tree_Node*a)
{
    Tree_Node *b;
    b = a->Right_Child;

    a->Right_Child  = b->Left_Child; //Mirroring of child from right to left
    b->Left_Child = a; //Now b become the root, or main Node

    a->H = 1 + max(Height_Calc(a->Right_Child), Height_Calc(a->Left_Child));
    b->H = 1 + max( b->Left_Child->H, b->Right_Child->H );

    return b;
}

Tree_Node* RL_Rotation(Tree_Node*t)
{
    Tree_Node*p = t->Right_Child;
    Tree_Node *x = t->Right_Child->Left_Child;
    t->Right_Child->Left_Child = x->Right_Child;
    t->Right_Child = x->Left_Child;

    x->Right_Child = p;
    x->Left_Child = t;

    p->H = 1 + max( Height_Calc(p->Left_Child), Height_Calc(p->Right_Child) );
    t->H = 1 + max( Height_Calc(t->Left_Child), Height_Calc(t->Right_Child) );
    x->H = 1 + max( p->H, t->H );

    return x;
}




void Enqueue( Tree_Node **data )
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

Tree_Node** Dequeue()
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

void Empty_My_Queue()
{
    while(Front)
    {
        Dequeue();
    }
}

int InO_P(Tree_Node** t)
{
    int temp;
    Tree_Node *s = *t, *follow = NULL;

    s = s->Left_Child;
    while( s->Right_Child )
    {
        follow = s;
        s = s->Right_Child;
    }

    if( !follow )
    {
        (*t)->Left_Child = NULL;
        temp = s->data;
        free(s);
        return temp;
    }
    else
    {
        follow->Right_Child = NULL;
        temp = s->data;
        free(s);
        return temp;
    }
}

int InO_S(Tree_Node** t)
{
    int temp;
    Tree_Node *s = *t, *follow = NULL;

    s = s->Right_Child;
    while( s->Left_Child )
    {
        follow = s;
        s = s->Left_Child;
    }

    if( !follow )
    {
        (*t)->Right_Child = NULL;
        temp = s->data;
        free(s);
        return temp;
    }
    else
    {
        follow->Left_Child = NULL;
        temp = s->data;
        free(s);
        return temp;
    }
}




int Height_Calc(Tree_Node* t)
{
    if(!t) return -1;
    else return t->H;
}

int Rec_H(Tree_Node *t)
{
    if( !t )
        return -1;
    else
    {
        t->H = 1 + max(Rec_H(t->Left_Child), Rec_H(t->Right_Child) );
        return t->H;
    }
}

int Rec_Delete(Tree_Node** t, int num)
{
    if( !(*t) ) return -1;
    if( (*t)->data > num )
    {
        (*t)->H = 1 + max( Rec_Delete(&(*t)->Left_Child, num), Height_Calc( (*t)->Right_Child) );
        *t = h_fix(t);
        return (*t)->H;
    }
    else if( (*t)->data < num )
    {
        (*t)->H = 1 + max( Rec_Delete(&(*t)->Right_Child, num), Height_Calc( (*t)->Left_Child) );
        *t = h_fix(t);
        return (*t)->H;
    }
    else    //Number found
    {
        if( !(*t)->Left_Child && !(*t)->Right_Child ) //is a leaf, deletion routine
        {
            Tree_Node *a = Root, *follow = NULL;
            while( a )  //Searching the number
            {
                if( a->data==num )  break;
                follow = a;
                if( a->data > num ) a = a->Left_Child;
                else a = a->Right_Child;
            }
            if( !follow ){ free(Root); Root = NULL; }
            else if( follow->Left_Child == a ) { follow->Left_Child = NULL; free(a); }
            else { follow->Right_Child = NULL; free(a); }
            return -1;
        }
        else//general routine
        {
            if((*t)->Right_Child)
            {
                (*t)->data = InO_S(t);    //IS
                (*t)->H = 1 + max( Rec_H((*t)->Left_Child), Rec_H((*t)->Right_Child) );
            }
            else
            {
                (*t)->data = InO_P(t);                     //IP
                (*t)->H = 1 + max( Rec_H((*t)->Left_Child), Rec_H((*t)->Right_Child) );
            }

            *t = h_fix(t);
            //fix operations

            return (*t)->H;
        }
    }
}

void Graph(Tree_Node *t)
{
    if( !t ) return;
    Graph(t->Left_Child);

    for( int i = 0; i<t->H; i++ ){ printf("\t"); }
    printf("%d\n", t->data);

    Graph(t->Right_Child);
}


int Search(Tree_Node*t, int num)
{
    if(!t){ return 0; }
    else if( t->data > num ){ return Search(t->Left_Child, num); }
    else if( t->data < num ){ return Search(t->Right_Child, num); }
    else return 1;
}
