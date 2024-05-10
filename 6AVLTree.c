//C Program to implemenet AVL Search Tree.

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int key;
	struct Node* l;
	struct Node* r;
	int height;
}Node;

int height(Node *N)
{
	if(N == NULL)
		return 0;
	return N-> height;
}

int max(int a,int b)
{
	return (a>b)? a:b;
}

Node* newNode(int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node ->key = key;
	node -> l = NULL;
	node -> r = NULL;
	node -> height = 1;
	return(node);
}

Node *rRotate(Node *y)
{
	Node *x = y -> l;
	Node *T2 = x -> r;
	
	x -> r = y;
	y -> l = T2;
	
	y -> height = max(height(y->l), height(y->r)) + 1;
	x -> height = max(height(x->l), height(x->r)) + 1;
	
	return x;
}

Node *lRotate(Node *x) {
    Node *y = x->r;
    Node *T2 = y->l;

    y->l = x;
    x->r = T2;

    x->height = max(height(x->l), height(x->r)) + 1;
    y->height = max(height(y->l), height(y->r)) + 1;

    return y;
}

int getBalance(Node *N)
{
	if(N == NULL)
		return 0;
	return height(N -> l) - height(N->r);
}


Node* insert(Node* node, int key) {
    // 1. Perform the normal BST insertion
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->l = insert(node->l, key);
    else if (key > node->key)
        node->r = insert(node->r, key);
    else // Equal keys are not allowed in the BST
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->l), height(node->r));

    // 3. Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // l l Case
    if (balance > 1 && key < node->l->key)
        return rRotate(node);

    // r r Case
    if (balance < -1 && key > node->r->key)
        return lRotate(node);

    // l r Case
    if (balance > 1 && key > node->l->key) {
        node->l = lRotate(node->l);
        return rRotate(node);
    }

    // r l Case
    if (balance < -1 && key < node->r->key) {
        node->r = rRotate(node->r);
        return lRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(Node *root) {
    if(root != NULL) {
        printf("%d ", root->key);
        preOrder(root->l);
        preOrder(root->r);
    }
}

int main() {
    Node *root = NULL;

    /* Constructing tree given in the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the constructed AVL tree is \n");
    preOrder(root);

    return 0;
}
