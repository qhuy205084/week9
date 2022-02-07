/*Write a program to build a
tournament: a binary tree where
the item in every internal Node is a
copy of the larger of the items in its
two children. So the root is a copy
of largest item in the tournament.
The items in the leaves constitute
the data of interest.
• The input items are stored in an
array.
• Hint: Uses a divide and conquer
strategy */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int value;
    struct Node *left, *right;
}Node;

void free(Node *root)
{
    if(root == NULL) return;
    free(root->left);
    free(root->right);
    free(root);
}
Node *create(int a, Node *left, Node *right)
{
    Node *x = (Node *)malloc(sizeof(Node));
    x -> value = a;
    x -> left = left;
    x -> right = right;
    return x;
}

Node *maketree(int a[], int l, int r)
{
    int m = (l+r) / 2;
    Node *x = create(a[m],NULL,NULL);
    if(l==r) return x;
    x -> left = maketree(a,l,m);
    x -> right = maketree(a, m+1, r);
    int u = x -> left -> value;
    int v = x -> right -> value;
    if(u > v) x -> value = u;
    else x -> value = v;
    return x;
}

void main()
{
    int a[10] = {1,2,3,4,13,4,7,8,10,11};
    Node *root = NULL;
    root = maketree(a,0,9);
    printf("%d ",root -> value);
    free(root);
}