#include"AVL.h"
#define scan(x) scanf("%d", &x)
#define CLR system("CLS")

int main()
{
    for(int i = 0; i<100; i++)
        RInsert(&Root, i);

    for(int i = 0; i<50; i++)
        Rec_Delete(&Root, i);

    PreOrder(Root);
    printf("\n\n\n");
    PostOrder(Root);
    printf("\n\n\n");
    InOrder(Root);
    printf("\n\n\n");
    LevelOrder(Root);

    Delete_My_Tree(Root);
}


