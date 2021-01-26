//Libraries in use
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//CLA = command line arguments for the program
#define CLA 2

//Given limits
#define MAXLINELENGTH 200
#define MAXWORD 25
#define MAXCARPRICE 1000000

typedef struct node {
        char *make;
        char *model;
		int price;
        int year;
        char *color;
        char *type;
		int mileage;
        struct node* left;
        struct node* right;
} node;

//prototypes
node* get_cars(char* filename);
node* add_to_tree(node* head, node* new);
void Free_Tree(node* root);
void search_tree(node* root, int year, int price, int* count);
int OpenFile(FILE **InPtr, char *argv);