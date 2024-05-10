//C Program to implemenet Stacks using Arrays.

#include<stdio.h>
#include<stdlib.h>

#define MAX 10  // Defining the maximum size of the stack

int stack[MAX];
int top = -1;

void push(int data) {
    if(top == MAX - 1) {
        printf("Stack overflow\n");
    } else {
        top++;
        stack[top] = data;
        printf("%d pushed to stack\n", data);
    }
}

int pop() {
    if(top == -1) {
        printf("Stack underflow\n");
        return -1;
    } else {
        int data = stack[top];
        top--;
        printf("%d popped from stack\n", data);
        return data;
    }
}

void display() {
    if(top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements are:\n");
        for(int i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}

int main() {
    push(10);
    push(20);
    push(30);
    display();
    pop();
    display();
    return 0;
}
