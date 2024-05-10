//C Program to implement circular queue using arrays.

#include<stdio.h>
#include<stdlib.h>

#define MAX 5

int q[MAX];
int f = -1, r = -1;

void enqueue(int data)
{
	if((f == 0 && r == MAX-1)|| (r == (f-1) % (MAX - 1)))
		printf("\nQueue is full");
	else
	{
		if( f == -1)
			f = r = 0;
		else if( r == MAX - 1 && f != 0)
			r = 0;
		else
			r++;
	q[r] = data;
	printf("\n%d Enqueued to Queue at location %d",data, r);
	}
}

int dequeue()
{
	if (f == -1)
	{
		printf("\nQueue is Empty");
		return -1;
	}
	
	int data = q[f];
	if (f == r)
		f = r = -1;
	else if( f == MAX -1)
		f = 0;
	else
		f++;
	printf("\n%d Dequeues from Queue", data);
	return data;
}

void display()
{
	if(f == -1)
		printf("\nQueue is empty");
	else
	{
		if(r >=f)
			for(int i = f; i<=r; i++)
				printf("%d", q[i]);
		else
		{
			for(int i = f; i<MAX;i++)
				printf("%d ", q[i]);
			for(int i = 0; i<=r;i++)
				printf("%d ", q[i]);
		}
		printf("\n");
	}
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display(); // Full queue
    dequeue(); // Removing one item
    dequeue(); // Removing another item
    display(); // Showing final queue
    enqueue(60); // Adding new item
    enqueue(70); // Adding another item
    display(); // Final display of circular nature
    return 0;
}
