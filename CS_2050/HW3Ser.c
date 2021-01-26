#include "HW3Lib.h"

void search_tree(node* root, int year, int price, int* count)
{
	if(price == 0)
	{
	if(root != NULL)
	{
	if(root->year >= year)
		{
			printf("\n%d %s %s that cost $%d", root->year, root->make, root->model, root->price);
		}
		if(root->price <= price && root->year <= year)
		{
			printf("\n%d %s %s that cost $%d", root->year, root->make, root->model, root->price);
		}
		search_tree(root->right, year, price, count);
		search_tree(root->left, year, price, count);
	}
	}
	else
	{
	if(year == 0)
	{
	if(root != NULL)
	{
		if(root->price <= price)
		{
			printf("\n%d %s %s that cost $%d", root->year, root->make, root->model, root->price);
		}
		search_tree(root->right, year, price, count);
		search_tree(root->left, year, price, count);
	}
	}
	else
	{
	if(year != 0 && price != 0)
	{
	if(root != NULL)
	{
	if(root->price <= price && root->year >= year)
		{
			printf("\n%d %s %s that cost $%d", root->year, root->make, root->model, root->price);
		}
		search_tree(root->right, year, price, count);
		search_tree(root->left, year, price, count);
	}
	}
	}
	}
}
