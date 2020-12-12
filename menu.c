#include"avl/avl.c"
#define clear system("clear")

int main()
{
    tree* my_tree = new_tree();

    int temp = 0;
    while(1)
    {
        clear;
        Graph(my_tree->Root);
        printf("\n1. Insertion\n2. Deletion\n ");
        scan(temp);
        if( temp == 1)
        {
            printf("\nEnter a number for insertion( -1 for termination ):-\t");
            scanf("%d", &temp);
            if( temp == -1 ){
                break;
            } 
            else {
                add_t(my_tree, temp);
            }
        }
        else
        {
            printf("\nEnter a number for deletion( -1 for termination ):-\t");
            scanf("%d", &temp);
            if( temp == -1 ){
                break;
            } 
            else{
                remove_t(my_tree, temp);
            } 
        }
    }

    delete_tree(my_tree);
    
    // getchar(); // for stopping your execution file
    return 0;
}


