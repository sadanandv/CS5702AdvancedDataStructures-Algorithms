//C program to implement Queues using Arrays

#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Maximum number of elements in the queue

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int data) {
    if (rear == MAX - 1) {
        printf("Queue overflow\n");
    } else {
        if (front == -1) // If queue is initially empty
            front = 0;
        rear++;
        queue[rear] = data;
        printf("%d enqueued to queue\n", data);
    }
}

int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue underflow\n");
        return -1;
    } else {
        int data = queue[front];
        front++;
        printf("%d dequeued from queue\n", data);
        if (front > rear) {  // Reset queue after last dequeue
            front = -1;
            rear = -1;
        }
        return data;
    }
}

void display() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements are:\n");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    display();
    return 0;
}

