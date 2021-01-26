#include "HW3Lib.h"

node *get_cars(char* filename)
{
node* root = NULL;
char whole[MAXLINELENGTH];
FILE *InPtr = NULL;
OpenFile(&InPtr, filename);
int testcount1 = 0;
int testcount2 = 0;

while(testcount1 != -1){
char* previous = NULL;
char* current = NULL;
if(fgets(whole, MAXLINELENGTH, InPtr) == NULL){break;}

node *temp = malloc(sizeof(node));

//printf("\n %s", whole);
	while(testcount2 < 7)
	{
	if (!current)
	{
		previous = strtok(whole, "|");
		current = strtok(NULL, "|");
		//printf("\n\n1.) %s %s\n\n", current, previous);
	}
	else
	{
		previous = strtok(NULL, "|");
		current = strtok(NULL, "|");
		//printf("\n\n2.) %s %s\n\n", current, previous);
	}
	if(strcmp(previous, "make") == 0)
	{
		temp->make = strdup(current);
		//printf("\n\nTest make load\n\n");
	}
	if(strcmp(previous, "model") == 0)
	{		
		temp->model = strdup(current);
	}
	if(strcmp(previous, "color") == 0)
	{
		temp->color = strdup(current);
	}
	if(strcmp(previous, "type") == 0)
	{
		temp->type = strdup(current);
	}
	if(strcmp(previous, "price") == 0)
	{
		temp->price = atoi(current);
	}
	if(strcmp(previous, "year") == 0)
	{
		temp->year = atoi(current);
	}
	if(strcmp(previous, "mileage") == 0)
	{
		temp->mileage = atoi(current);
	}
	testcount2++;
	}
temp->left = NULL;
temp->right = NULL;
root = add_to_tree(root, temp);
testcount2 = 0;
}
fclose(InPtr);
return root;
}

void Free_Tree(node* root)
{
	if(root != NULL)
	{
	//printf("\n\n Make: %s\n  Model: %s\n  Price: %d\n  Year: %d\n  Colour: %s\n  Type: %s\n  Mileage: %d \n\n", root->make, root->model, root->price, root->year, root->color, root->type, root->mileage);
	Free_Tree(root->left);
	Free_Tree(root->right);
	free(root->make);
	free(root->model);
	free(root->color);
	free(root->type);
	free(root);
	}
}

node* add_to_tree(node* root, node* leaf)
{
if(root == NULL)
	{
	return leaf;
	}
if(leaf->price <= root->price)
{
root->left = add_to_tree(root->left, leaf);
}
else
{
root->right = add_to_tree(root->right, leaf);
}
return (root);
}

int OpenFile(FILE **InPtr, char *argv)
{
int State = 1;
*InPtr = fopen(argv, "r");
if(*InPtr == NULL){printf("\nFile failed to load at open..."); State = 0;}
return (State);
}