#include "HW3Lib.h"

int main (int argc, char *argv[])
{
	//Declare variables
	node *root = NULL;
	char* File_Name = argv[1];
	int choice = 0;
	int year = 0;
	int price = 0;
	int count = 0;
	
	//argument enforcement
	if(argc != 2)
	{
		printf("\tInvalid Use of Program\n\tValid Use: 'Program Name' input.txt\n");
	}
	
	root = get_cars(File_Name);
	
	while(choice != -1)
	{
	count = 0;
	year = 0;
	price = 0;
	count = 0;
	
	printf("\nTo search for a vehicle newer than a specific year enter '1'");
	printf("\nTo search for a vehicle that costs less than a certain price enter '2'");
	printf("\nTo search for a vehicle with both of the above parameters enter '3'");
	printf("\nTo exit enter '-1' :    ");
	
	scanf("%d", &choice);
	
	if(choice == 1)
	{
		printf("\nEnter year: ");
		scanf("%d", &year);
		search_tree(root, year, price, &count);
	}
	if(choice == 2)
	{
		printf("\nEnter price: ");
		scanf("%d", &price);
		search_tree(root, year, price, &count);
	}
	if(choice == 3)
	{
		printf("\nEnter year: ");
		scanf("%d", &year);
		printf("\nEnter price: ");
		scanf("%d", &price);
		search_tree(root, year, price, &count);
	}
	}
	
	Free_Tree(root);
	//printf("\n\nFree ran....");
	
return(0);	
}
