/*
• Implement BFS algorithm in C 
language
• Add this function to the binary tree 
library
• Test it the Phone Book management 
program to print all the names in the 
tree.
• Output the results to a file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef struct Node
{
    char name[MAX];
    char telephone_number[MAX];
    char email_address [MAX];
    struct Node *left,*right;
}Node;

int leftof(char email_address[],Node *root)
{
    return strcmp(email_address,root->email_address) < 0;
}

int rightof(char email_address[], Node *root)
{
    return strcmp(email_address,root->email_address) > 0;
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
    else if(leftof(email_address,root))
    {
        root -> left = Insert(name, telephone_number, email_address,root->left);
    }
    else if(rightof(email_address,root))
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

Node *queue[20];
int front = 0, rear = -1;
bool empty()
{
    if(rear < front) return true;
    else return false;
}

bool full()
{
    if(rear - front >= 10) return true;
    else return false;
}

Node *dequeue()
{
    if(empty()==true) printf("Queue is empty\n");
    else
    {
        front++;
        return queue[front-1];
    }
}

void enqueue(Node *p)
{
    rear++;
    queue[rear] = p;
}

void BFS(Node *p)
{
    if(p!=NULL)
    {
        enqueue(p);
        while(!empty())
        {
            p = dequeue();
            printf("%s ",p->name);
            if(p->left!=NULL)
            {
                enqueue(p->left);
            }
            if(p->right!=NULL)
            {
                enqueue(p->right);
            }
        }
    }

}

void Free(Node *root)
{
    if(root == NULL) return;
    Free(root-> left);
    Free(root->right);
    Free(root);
}

void main()
{
    Node *root = NULL;
    root = Input(root);
    BFS(root);
    Free(root);
}