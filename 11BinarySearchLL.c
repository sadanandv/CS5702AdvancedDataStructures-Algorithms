#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void insertAtHead(Node** head, int data);
void printList(Node* head);
void freeList(Node* head);
int listLength(Node* head);
Node* getNodeAtPosition(Node* head, int position);
int binarySearchLike(Node* head, int target);

int main() {
    Node* head = NULL;

    // Inserting elements
    insertAtHead(&head, 60);
    insertAtHead(&head, 55);
    insertAtHead(&head, 38);
    insertAtHead(&head, 28);
    insertAtHead(&head, 13);
    insertAtHead(&head, 8);

    printList(head);

    int target = 8;
    int position = binarySearchLike(head, target);
    if (position != -1) {
        printf("Element %d found at position: %d\n", target, position);
    } else {
        printf("Element %d not found in the list\n", target);
    }

    freeList(head);

    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Could not allocate memory for new node\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int listLength(Node* head) {
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

Node* getNodeAtPosition(Node* head, int position) {
    int count = 0;
    Node* current = head;
    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }
    return current;
}

int binarySearchLike(Node* head, int target) {
    int start = 0;
    int end = listLength(head) - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        Node* midNode = getNodeAtPosition(head, mid);
        if (midNode->data == target) {
            return mid;
        } else if (midNode->data < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return -1;
}