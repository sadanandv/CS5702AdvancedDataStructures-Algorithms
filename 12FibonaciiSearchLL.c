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
int fibonacciSearch(Node* head, int target);
int min(int x, int y);

int main() {
    Node* head = NULL;

    insertAtHead(&head, 235);
    insertAtHead(&head, 100);
    insertAtHead(&head, 90);
    insertAtHead(&head, 85);
    insertAtHead(&head, 82);
    insertAtHead(&head, 80);
    insertAtHead(&head, 50);
    insertAtHead(&head, 45);
    insertAtHead(&head, 40);
    insertAtHead(&head, 35);
    insertAtHead(&head, 22);
    insertAtHead(&head, 10);

    printList(head);

    int target = 85;
    int position = fibonacciSearch(head, target);

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
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
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
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
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
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

Node* getNodeAtPosition(Node* head, int position) {
    int index = 0;
    Node* current = head;
    while (current != NULL && index < position) {
        current = current->next;
        index++;
    }
    return current;
}

int fibonacciSearch(Node* head, int target) {
    int fibM_minus_2 = 0;
    int fibM_minus_1 = 1;
    int fibM = fibM_minus_2 + fibM_minus_1;

    int n = listLength(head);

    while (fibM < n) {
        fibM_minus_2 = fibM_minus_1;
        fibM_minus_1 = fibM;
        fibM = fibM_minus_2 + fibM_minus_1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibM_minus_2, n - 1);

        Node* iNode = getNodeAtPosition(head, i);

        if (!iNode || iNode->data < target) {
            fibM = fibM_minus_1;
            fibM_minus_1 = fibM_minus_2;
            fibM_minus_2 = fibM - fibM_minus_1;
            offset = i;
        } else if (iNode->data > target) {
            fibM = fibM_minus_2;
            fibM_minus_1 = fibM_minus_1 - fibM_minus_2;
            fibM_minus_2 = fibM - fibM_minus_1;
        } else {
            return i;
        }
    }

    if (fibM_minus_1 && getNodeAtPosition(head, offset + 1)->data == target) {
        return offset + 1;
    }

    return -1;
}

int min(int x, int y) {
    return (x <= y) ? x : y;
}