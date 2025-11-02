#include<stdio.h>
#define Max_Size 100

int stack[Max_Size];
int top = -1;

void push();
void pop();
void peek();
void display();

int main()
{
	int opt;
	
	do
{
	printf("\t\t|===STACK===|\n\t\t-------------\n\n");
	printf("1)PUSH: Insert an element into the stack.\n");
	printf("2)POP: Remove the top element from the stack.\n");
	printf("3)PEEK: Display the top element without removing it.\n");
	printf("4)DISPLAY: Show all elements currently in the stack.\n");
	printf("5)EXIT: Terminate the program.\n");
	printf("ENTER YOUR OPERATION TO PERFORM ON THE STACK:\t\t");
	scanf("%d", &opt);
	
	switch (opt)
	{
		case 1:
				push();
				break;	
		case 2:
				pop();
				break;	
		case 3:
				peek();
				break;
		case 4:
				display();
				break;	
		case 5:
				break;		
        default:
                printf("INVALID CHOICE! ENTER FROM 1 TO 5 ONLY.\n");
	}
} while(opt != 5);
}

	
void push()
{
	printf("----------------------------------------------------------------------------\n\t\t\t==PUSHING ELEMENT==\n");
	int value;
	
	if (top == Max_Size - 1)
	{
		printf("\nSTACK IS FULL! CANNOT INSERT MORE ELEMENTS.\n");
		printf("\n-----------------------------------------------------------------------------\n");	
		return;
	}
	
		printf("\nENTER THE VALUE OF THE ELEMENT YOU WANT TO INSERT:\t");
		scanf("%d", &value);
		
		top++;
		stack[top] = value;
		printf("ELEMENT %d IS SUCCESSFULLY PUSHED IN [%d] OF THE STACK!", value, top);
		printf("\n-----------------------------------------------------------------------------\n");
}

void pop()
{
		printf("----------------------------------------------------------------------------\n\t\t\t==POPING ELEMENT==\n");	
		
		if(top == -1)
		{
			printf("\nSTACK IS EMPTY! CANNOT POP ANY ELEMENT.\n");
			printf("\n-----------------------------------------------------------------------------\n");
			return;
		}
		int remove = stack[top];
		top--;
		printf("ELEMENT %d IS SUCCESSFULLY POPPED FROM [%d] OUT OF THE STACK", remove, top+1);
		printf("\n-----------------------------------------------------------------------------\n\n");
}

void peek()
{
	printf("----------------------------------------------------------------------------\n\t\t\t==PEEKING ELEMENT==\n");
	if(top == -1)
	{
		printf("STACK IS EMPTY!\n");
		printf("\n-----------------------------------------------------------------------------\n\n");
		return;
	}	
	printf("%d", stack[top]);
		printf("\n-----------------------------------------------------------------------------\n\n");
}

void display()
{
	printf("----------------------------------------------------------------------------\n\t\t\t==DISPLAYING ELEMENT==\n");
	if(top == -1)
	{
		printf("STACK IS EMPTY!\n");
		printf("\n-----------------------------------------------------------------------------\n\n");
		return;
	}	
	
	for (int i = top; i>=0; i--)
	{
		printf("%d) %d\n", i+1, stack[i]);	
	}
	printf("\n-----------------------------------------------------------------------------\n\n");
}
