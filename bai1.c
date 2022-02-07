/*
Return to the exercise lastweek. We 
have already a tree for storing Phone 
address book. 
• Now output all the data stored in the 
binary tree in ascending order for the 
e-mail address.
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

Node *makenode(char name[], char telephone_number[], char email_address[])
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->telephone_number, telephone_number);
    strcpy(p->email_address, email_address);
    p -> left = NULL;
    p -> right = NULL;
    return p;
}

Node *Insert(char name[], char telephone_number[], char email_address[], Node *root)
{
    if(root == NULL) return makenode(name, telephone_number, email_address);
    int c = strcmp(root->email_address, email_address);
    if(c == 0)
    {
        printf("Dia chi %s da ton tai!\n",email_address);
        return root;
    }
    else if(c < 0)
    {
        root -> right = Insert(name, telephone_number, email_address, root -> right);
        return root;
    }
    else if(c > 0)
    {
        root -> left = Insert(name, telephone_number, email_address, root -> left);
        return root;
    }
}

void Inorder(Node *root)
{
    if(root != NULL)
    {
        Inorder(root -> left);
        printf("%s %s %s\n", root -> name, root -> telephone_number, root -> email_address);
        Inorder(root -> right);
    }
}

void main()
{
    Node *root = NULL;
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL)
    {
        printf("Can't open input file.\n");
    }
    else
    {
        while(!feof(fp))
        {
            char name[MAX], telephone_number[MAX], email_address[MAX];
            fscanf(fp,"%s %s %s", name, telephone_number, email_address);
            root = Insert(name, telephone_number,email_address,root);
        }
    }
    fclose(fp);
    printf("\n==The data stored in the binary tree in ascending order for the email address\n==\n");
    Inorder(root);   
}