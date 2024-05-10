//C Program to implemenet binary Search Tree.

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node* l;
	struct Node* r;
}Node;

Node* createNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		printf("\nError creaing new Node");
		exit(0);
	}
	newNode -> data = data;
	newNode -> l = NULL;
	newNode -> r = NULL;
	return newNode;
}

Node* insert(Node* node, int data)
{
	if(node == NULL)
		return createNode(data);
	if(data< node -> data)
		node -> l = insert(node ->l, data);
	else if(data> node -> data)
		node -> r = insert(node -> r, data);
	
	return node;
}

void inorder(Node *root)
{
	if(root != NULL)
	{
		inorder(root -> l);
		printf("%d ", root -> data);
		inorder(root -> r);
	}
}

Node* search(Node* root, int key)
{
	if(root == NULL || root -> data == key)
		return root;
	if(root -> data < key)
		return search(root -> r, key);
	
	return search(root -> l, key);
}


Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->l != NULL)
        current = current->l;
    return current;
}

Node* deleteNode(Node* root, int data) {
    // Base case: The tree is empty
    if (root == NULL)
        return root;

    // If the data to be deleted is smaller than the root's data,
    // it lies in the left subtree
    if (data < root->data)
        root->l = deleteNode(root->l, data);

    // If the data to be deleted is greater than the root's data,
    // then it lies in the right subtree
    else if (data > root->data)
        root->r = deleteNode(root->r, data);

    // If data is the same as root's data, then this is the node
    // to be deleted
    else {
        // Node with only one child or no child
        if (root->l == NULL) {
            Node* temp = root->r;
            free(root);
            return temp;
        } else if (root->r == NULL) {
            Node* temp = root->l;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        Node* temp = minValueNode(root->r);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->r = deleteNode(root->r, temp->data);
    }
    return root;
}

int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the given tree: \n");
    inorder(root);
    printf("\n");


    int key = 65;
    Node* result = search(root, key);
    if (result != NULL) {
        printf("Element %d found in the BST.\n", key);
    } else {
        printf("Element %d not found in the BST.\n", key);
        
      
    }

    return 0;
}
