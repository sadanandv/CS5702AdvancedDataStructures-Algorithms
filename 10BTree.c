#include <stdio.h>
#include <stdlib.h>

// A BTree node
typedef struct BTreeNode {
    int *keys;          // An array of keys
    int t;              // Minimum degree (defines the range for number of keys)
    struct BTreeNode **C; // An array of child pointers
    int n;              // Current number of keys
    int leaf;           // Is true when node is leaf. Otherwise false
} BTreeNode;


BTreeNode* createNode(int t, int leaf);
void insertNonFull(BTreeNode* node, int k);
void splitChild(BTreeNode* parent, int i, BTreeNode* y);
void traverse(BTreeNode* root);
void insert(BTreeNode** rootRef, int k, int t);


// A utility function to create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->t = t;
    newNode->leaf = leaf;
    newNode->keys = (int*)malloc((2*t-1) * sizeof(int));
    newNode->C = (BTreeNode**)malloc(2*t * sizeof(BTreeNode*));
    newNode->n = 0;
    return newNode;
}

// A utility function to insert a new key in this node
void insertNonFull(BTreeNode* node, int k) {
    int i = node->n - 1; // Initialize i as index of right-most element

    // If this is a leaf node
    if (node->leaf) {
        // Find the location of new key to be inserted and move all greater keys to one place ahead
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i+1] = node->keys[i];
            i--;
        }

        // Insert the new key at found location
        node->keys[i+1] = k;
        node->n = node->n + 1;
    } else { // If this node is not leaf
        // Find the child which is going to have the new key
        while (i >= 0 && node->keys[i] > k)
            i--;

        // See if the found child is full
        if (node->C[i+1]->n == 2*node->t-1) {
            splitChild(node, i+1, node->C[i+1]);

            // After split, the middle key of C[i] goes up and C[i] is split into two. See which of the two is going to have the new key
            if (node->keys[i+1] < k)
                i++;
        }
        insertNonFull(node->C[i+1], k);
    }
        printf("\nValue has been inserted");
}

// A utility function to split the child y of this node. i is index of y in child array C[]
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    // Create a new node which is going to store (t-1) keys of y
    BTreeNode* z = createNode(y->t, y->leaf);
    z->n = parent->t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < parent->t-1; j++)
        z->keys[j] = y->keys[j + parent->t];

    // Copy the last t children of y to z
    if (!y->leaf) {
        for (int j = 0; j < parent->t; j++)
            z->C[j] = y->C[j + parent->t];
    }

    // Reduce the number of keys in y
    y->n = parent->t - 1;

    // Since this node is going to have a new child, create space of new child
    for (int j = parent->n; j >= i+1; j--)
        parent->C[j+1] = parent->C[j];

    // Link the new child to this node
    parent->C[i+1] = z;

    // A key of y will move to this node. Find the location of new key and move all greater keys one space ahead
    for (int j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    // Copy the middle key of y to this node
    parent->keys[i] = y->keys[parent->t-1];
    parent->n = parent->n + 1;
    printf("\nNode has been split");
 
}

// Function to traverse all nodes in a subtree rooted with this node
void traverse(BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        // If this is not leaf, then before printing key[i], traverse the subtree rooted with child C[i].
        if (!root->leaf)
            traverse(root->C[i]);
        printf("%d ", root->keys[i]);
    }

    // Print the subtree rooted with last child
    if (!root->leaf)
        traverse(root->C[i]);
}

// The main function that inserts a new key in this B-Tree
void insert(BTreeNode** rootRef, int k, int t) {
    BTreeNode* root = *rootRef;
    // If tree is empty
    if (root == NULL) {
        root = createNode(t, 1);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
        *rootRef = root;
    } else { // If tree is not empty
        // If root is full, then tree grows in height
        if (root->n == 2*t-1) {
            BTreeNode* s = createNode(t, 0);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            splitChild(s, 0, root);

            // New root has two children now. Decide which of the two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->C[i], k);

            // Change root
            *rootRef = s;
        } else  // If root is not full, call insertNonFull for root
              insertNonFull(root, k);
    }
}

// A utility function to search a key in a subtree rooted with this node
BTreeNode* searchKey(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && k == root->keys[i])
        return root;
    if (root->leaf)
        return NULL;

    return searchKey(root->C[i], k);
}


// Driver program to test above functions
int main() {
    BTreeNode* root = NULL;
    int t = 3; // A B-Tree of minimum degree 3
    insert(&root, 10, t);
    insert(&root, 20, t);
    insert(&root, 5, t);
    insert(&root, 6, t);
    insert(&root, 12, t);
    insert(&root, 30, t);
    insert(&root, 7, t);
    insert(&root, 17, t);

    printf("Traversal of the constructed B-tree is:\n");
    traverse(root);
    printf("\n");

    int keysToFind[] = {6, 15, 30, 100};
    for (int i = 0; i < sizeof(keysToFind) / sizeof(keysToFind[0]); i++) {
        BTreeNode* found = searchKey(root, keysToFind[i]);
        if (found != NULL) {
            printf("Key %d found in the tree.\n", keysToFind[i]);
        } else {
            printf("Key %d not found in the tree.\n", keysToFind[i]);
        }
    }

    return 0;
}


