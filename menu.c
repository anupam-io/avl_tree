#include"avl/avl.c"
#define clear system("clear")

int main()
{
    tree* my_tree = new_tree();

    int temp = 0;
    while(1)
    {
        // clear;
        printf("--------------------\n");
        Graph(my_tree->Root);
        printf("\n1. Insertion\n2. Deletion\n3. Search \n ");
        scanf("%d", &temp);
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
        else if(temp == 2)
        {
            printf("\nEnter a number for deletion( -1 for termination ):-\t");
            scanf("%d", &temp);
            if( temp == -1 ){
                break;
            } 
            else{
                remove_t(my_tree, temp);
            } 
        } else {
            printf("\nEnter a number for deletion( -1 for termination ):-\t");
            scanf("%d", &temp);
            if( temp == -1 ){
                break;
            } 
            else{
                int ret = find_t(my_tree, temp);
                if(ret == 0){
                    printf("Not found.\n");
                } else {
                    printf("Found.\n");
                }
                getchar();
            }
        }
    }

    delete_tree(my_tree);
    
    return 0;
}