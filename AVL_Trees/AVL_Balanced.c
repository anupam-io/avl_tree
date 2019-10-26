#include"AVL.h"
#define scan(x) scanf("%d", &x)
#define CLR system("CLS")

int main()
{
    RInsert( &Root, 50);
    RInsert( &Root, 75);
    RInsert( &Root, 25);
    RInsert( &Root, 19);
    RInsert( &Root, 29);
    RInsert( &Root, 88);
    RInsert( &Root, 65);
    RInsert( &Root, 61);
    RInsert( &Root, 59);
    RInsert( &Root, 71);
    printf( "\nHello all insertions done\n\n" );

    Rec_Delete(&Root, 61);
    Rec_Delete(&Root, 59);


    PreOrder(Root);

    Delete_My_Tree(Root);
}


