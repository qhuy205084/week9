/*
Output all the data stored in the
binary tree in ascending dictionnary
order for the name in the Phone
Book Tree:
to screen
to a file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Node
{
    char name[MAX];
    char telephone_number[MAX];
    char email_address[MAX];
    struct Node *left, *right;
}Node;

void Free(Node *root)
{
    if(root == NULL) return;
    Free(root ->left);
    Free(root ->right);
    Free(root);
}

int leftof(char name[], Node *root)
{
    return strcmp(name,root->name) < 0;
}

int rightof(char name[], Node *root)
{
    return strcmp(name,root->name) > 0;
}

Node *Insert(char name[], char telephone_number[], char email_address[], Node *root)
{
    if(root == NULL)
    {
        Node *p = (Node *) malloc(sizeof(Node));
        strcpy(p->name, name);
        strcpy(p->telephone_number, telephone_number);
        strcpy(p->email_address, email_address);
        p -> left = NULL;
        p -> right = NULL;
        return p;
    }
    else if(leftof(name,root))
    {
        root -> left = Insert(name, telephone_number, email_address,root->left);
    }
    else if(rightof(name,root))
    {
        root -> right = Insert(name, telephone_number, email_address, root -> right);
    }
    return root;
}

Node *Input(Node *root)
{
    FILE *f = fopen("input.txt","r");
    if(f == NULL) printf("Can't open input file.\n");
    else
    {
        char name[MAX], telephone_number[MAX], email_address[MAX];
        while(fscanf(f,"%s %s %s\n",name,telephone_number, email_address)!=EOF)
        {
            root = Insert(name, telephone_number, email_address,root);
        }
    }
    return root;
    fclose(f);
}

void Inorder(Node *root)
{
    if(root!= NULL)
    {
        Inorder(root-> left);
        printf("%s %s %s\n",root -> name, root -> telephone_number, root -> email_address);
        Inorder(root -> right);
    }
}

void main()
{
    Node *root = NULL;
    root = Input(root);
    Inorder(root);
    Free(root);
}