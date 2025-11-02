#include<stdio.h>
#include<string.h>
#define max_books 100
int isbn[100]; 
int quantities[100];
int count = 0;
char title[100][50];
float prices[100]; 

void addBook();
void process();
void lowStock();

int main()
{
	int choice;
do
{	
	printf(" ===LIBRARY INVENTORY SYSTEM===\n|------------------------------|\n");
	printf("1) ADD NEW BOOK\n");
	printf("2) PROCESS A SALE\n");
	printf("3) GENERATE LOW-STOCK REPORT\n");
	printf("4) EXIT\n");
	
	printf("ENTER YOUR CHOICE:\t\t");
	scanf("%d", &choice);
	printf("\n");
	switch (choice)
	{
		case 1:
				addBook();
				break;
		case 2:
				process();
				break;
		case 3:
				lowStock();
				break;		
		case 4:
				break;
		default:
				printf("Invalid choice!\n");
				
	}	
} while (choice != 4);

}

void addBook()
{
		if(count>=100)
	{
		printf("INVENTORY FULL! CANNOT ADD MORE BOOKS\n");
		return;
	}
	
	int isbns;
	printf("\nENTER THE ISBN NUMBER OF THE BOOK:\t\t");
	scanf("%d", &isbns);
	for (int i=0; i<count; i++)
	{
		if(isbn[i] == isbns)
		{
			printf("ERROR: A BOOK ALREADY EXIST WITH THIS ISBN!\n\n");
			return;
		}
	}
	
	getchar();
	printf("ENTER THE TITLE OF THE BOOK:\t\t\t");
	fgets(title[count], sizeof(title[count]), stdin);
	for (int i=0; i<count; i++)
	{
		if (strcmp(title[i], title[count]) == 0)
		{
			printf("ERROR: A BOOK ALREADY EXIST WITH THIS TITLE!\n\n");
			return;
		}
	}
	printf("ENTER THE PRICE OF THE BOOK:\t\t\t");
	scanf("%f", &prices[count]);
	printf("ENTER THE QUANTITY OF THE BOOK\t\t\t");
	scanf("%d", &quantities[count]);
	
	printf("\n ===BOOK ADDED SUCCESSFULLY===\n|------------------------------|\n\n");
	isbn[count] = isbns;
	count++;
}
void process()
{	
	int isbns, soldQuantity;
	if(count == 0)
	{
		printf("THERE IS NO BOOKS IN THE INVENTORY\n");
		return;
	}
	printf("ENTER THE ISBN NUMBER OF THE SELLING BOOK:\t");
	scanf("%d", &isbns);
	
	for (int i=0; i<count; i++)
	{
		if(isbn[i] == isbns)
		{
			printf("HOW MANY BOOKS YOU WANT TO SELL:\t\t");
			scanf("%d", &soldQuantity);
			if(soldQuantity > quantities[i])
			{
				printf("NOT ENOUGH STOCK!\n");
				return;
			}
			else
			{
				quantities[i] -= soldQuantity;
				printf("SALE PROCESSED: REMAINING STOCKS LEFT ARE %d.\n\n", quantities[i]);
				return;
			}
		}
		
		printf("BOOK WITH THE ISBN NUMBER %d IS NOT FOUND.\n", isbns);	
	}
}
void lowStock()
{
	int status = 0;
	printf("\n=== LOW STOCK REPORT (Quantity < 5) ===\n");
	for (int i=0; i<count; i++)
	{
	if(quantities[i] < 5)
	{
		printf("ISBN NUMBER = %d\t| TITLE = %sPRICE = %d\t| QUANTITY = %d\n\n", isbn[i], title[i], prices[i], quantities[i]);
		status = 1;
	}
	}
	if(!status)
	{
		printf("\nEVERY THING IS STACKED, NO LOW-STOCK PRODUCT FOUND!\n\n");	
		return;
	}	
}
