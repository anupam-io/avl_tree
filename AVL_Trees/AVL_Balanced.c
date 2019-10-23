#include"AVL.h"
#define scan(x) scanf("%d", &x)
#define CLR system("CLS")

int main()
{
    int i = 100;
    while(i--)
    {
        RInsert(&Root, i);
    }
    printf("\n\n\n\n");
    PreOrder(Root);
    printf("\n\n\n\n");
    InOrder(Root);
    printf("\n\n\n\n");
    LevelOrder(Root);

    Delete_My_Tree(Root);
}


