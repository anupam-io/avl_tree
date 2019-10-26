#include"AVL.h"
#define scan(x) scanf("%d", &x)
#define CLR system("CLS")

int main()
{

    int temp = 0;
    while(1)
    {
        CLR;
        Graph(Root);
        printf("\n1. Insertion\n2. Deletion\n ");
        scan(temp);
        if( temp == 1)
        {
            printf("\nEnter a number for insertion( -1 for termination ):-\t");
            scan(temp);
            if( temp == -1 ) break;
            else RInsert(&Root, temp);
        }
        else
        {
            printf("\nEnter a number for deletion( -1 for termination ):-\t");
            scan(temp);
            if( temp == -1 ) break;
            else Rec_Delete(&Root, temp);
        }
    }

    Delete_My_Tree(Root);
    getchar(); // for stopping your execution file
    return 0;
}


