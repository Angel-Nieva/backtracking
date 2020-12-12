#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *rigth;
    struct node *left;
} tree;




typedef struct n
{
    int value;
    struct n **list_node;

} mtree;

void print_tree(tree *current)
{

    if (current == NULL)
    {
        return;
    }
    else
    {
        printf("%d \n", current->value);
        print_tree(current->left);
        print_tree(current->rigth);

        return;
    }
}

void print_mtree(mtree *current)
{

    if (current == NULL)
    {
        return;
    }
    else
    {
        printf("%d \n", current->value);

        if (current->list_node != NULL)
        {
            for (int i = 0; i < 5; i++)
            {
                print_mtree(current->list_node[i]);
            }
        }

        return;
    }
}

int main(int argc, char const *argv[])
{
    tree *arbol = (tree *)malloc(sizeof(tree));
    arbol->value = 1;

    arbol->left = (tree *)malloc(sizeof(tree));
    arbol->left->value = 2;
    arbol->left->left = NULL;
    arbol->left->rigth = NULL;

    arbol->rigth = (tree *)malloc(sizeof(tree));
    arbol->rigth->value = 3;
    arbol->rigth->left = NULL;
    arbol->rigth->rigth = NULL;

    print_tree(arbol);

    // ----------------------------


     mtree *longTree = (mtree *)malloc(sizeof(mtree));

     longTree->value = 1;

     longTree->list_node = (mtree **)malloc(sizeof(mtree *) * 5);

     for (int i = 0; i < 5; i++)
     {
         longTree->list_node[i] = (mtree *)malloc(sizeof(mtree));
         longTree->list_node[i]->value = i + 2;
         longTree->list_node[i]->list_node = NULL;
     }

     print_mtree(longTree);

    return 0;
	// holaaaaaaaa
}
