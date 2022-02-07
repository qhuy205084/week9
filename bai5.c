/*
Use a binary search tree (it's even better with AVL) to store data.
A node in this tree should contain at least two fields:
+ word: string
+ count: int
Word are stored in nodes in the dictionary order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct Node
{
    char word[MAX];
    int count;
    struct Node *left, *right;
}Node;

Node *Insert(char word[], Node *root)
{
    if(root == NULL)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        strcpy(p->word, word);
        p -> count = 1;
        p -> left = NULL;
        p -> right = NULL;
        return p;
    }
        int a = strcmp(word, root -> word);
        if(a == 0)
        {
            root -> count++;
        }
        else if(a < 0)
        {
            root -> left = Insert(word,root -> left);
        }
        else if(a > 0)
        {
            root -> right = Insert(word,root -> right);
        }
        return root;
    
}

Node *Input(Node *root)
{
    FILE *f = fopen("input2.txt","r");
    if(f == NULL) printf("Can't open input file.\n");
    else
    {
        char word[MAX]; 
        while(fscanf(f,"%s ",word)!=EOF)
        {
            root = Insert(strupr(word),root);
        }
    }
    return root;
    fclose(f);
}

void Inorder(Node *root)
{
    if(root != NULL)
    {
        Inorder(root -> left);
        printf("%s %d\n",root->word,root->count);
        Inorder(root -> right);
    }
}

void Free(Node *root)
{
    if(root == NULL) return;
    Free(root->left);
    Free(root->right);
    Free(root);
}

void main()
{
    Node *root = NULL;
    root = Input(root);
    Inorder(root);
    Free(root);
}
