//Libraries in use
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//house short cuts
#define p printf
#define s scanf
#define fp fprintf
#define fs fscanf
#define ROUNDS 3
#define MAX_NAME 25

#define CLA 7
//CLA = command line arguments for the program

typedef struct Player{
	char* Full_Name;
	int Player_ID;
	double Batting_Rate;
	double Defense_Rate;
	double Pitch_Rate;
}Player;

typedef struct node{

Player player;
struct node* next;
}node;


//prototypes
void addnode(node **StartPtr, char* NAME, int ID, double Bat, double Def, double Pit);
int OpenFile(FILE **InPtr, char *argv);
void MakeList(char* argv, node **StartPtr, int Limit);
void FreeNodes(node **StartPtr);
void PrintNodes(node **StartPtr);
void SearchList(node **StartPtr, node **NewList, int ID);
void draft(node **TeamAStart, node **TeamBStart, node **TeamCStart, node **DraftList, char* argv1, char* argv2, char* argv3, char* argv4);
double Average(node *Team);
void WhoWon(node *TeamAStart, node *TeamBStart, node *TeamCStart);

int main(int argc, char *argv[])
{
//Declare pointers
struct node* DraftList = NULL;
struct node* TeamAStart = NULL;
struct node* TeamBStart = NULL;
struct node* TeamCStart = NULL;
int Limit = atoi(argv[1]);

if(argc != CLA){p("\nIncorrect number of command line arguments...%d \n%d are needed.", argc, CLA); return(0);}
MakeList(argv[2], &DraftList, Limit);

p("\nPre-Draft Player List");
PrintNodes(&DraftList);

draft(&TeamAStart, &TeamBStart, &TeamCStart, &DraftList, argv[3], argv[4], argv[5], argv[6]);

p("\n\n\nPost-Draft Player List");
p("\nTeam A");
PrintNodes(&TeamAStart);

p("\nTeam B");
PrintNodes(&TeamBStart);

p("\nTeam C");
PrintNodes(&TeamCStart);

p("\nUndrafted");
PrintNodes(&DraftList);

WhoWon(TeamAStart, TeamBStart, TeamCStart);

FreeNodes(&TeamAStart);
FreeNodes(&TeamBStart);
FreeNodes(&TeamCStart);
FreeNodes(&DraftList);
return (0);
}

void SearchList(node **StartPtr, node **TeamList, int ID)
{
node *Utility;
node *Previous = NULL;
node *Current = *StartPtr;

	if(ID == (*StartPtr)->player.Player_ID)
	{
		Utility = (*StartPtr);
		Utility->player.Full_Name = (*StartPtr)->player.Full_Name;
		(*StartPtr) = (*StartPtr)->next;
		Utility->next = NULL;
		if((*TeamList) == NULL)
		{
			(*TeamList) = Utility;
		}
		else
		{
			Previous = (*TeamList);
			Current = (*TeamList)->next;
			while(Current != NULL)
			{
				Previous = Current;
				Current = Current->next;
			}
			Previous->next = Utility;
		}
	}
	else
	{
	Current = (*StartPtr);
		while(Current != NULL && Current->player.Player_ID != ID)
		{
		Previous = Current;
		Current = Current->next;
		}
	if(Current != NULL)
	{
		Utility = Current;
		Utility->player.Full_Name = Current->player.Full_Name;
		Previous->next = Current->next;
		Utility->next = NULL;
		if((*TeamList) == NULL)
		{
			(*TeamList) = Utility;
		}
		else
		{

			Previous = (*TeamList);
			Current = (*TeamList)->next;
			while(Current != NULL)
			{
				Previous = Current;
				Current = Current->next;
			}
			Previous->next = Utility;
			
		}
	
	}
	}
}

void PrintNodes(node **StartPtr)
{
node *Current = NULL;
Current = (*StartPtr);
if(Current == NULL){p("\nThe List is Empty...");}
while(Current != NULL)
{

p("\nPLAYER ID %d\n", (Current)->player.Player_ID);
p("Name: %s ", Current->player.Full_Name);
p("Batting: %.0lf ", (Current)->player.Batting_Rate);
p("Defense %.0lf ", (Current)->player.Defense_Rate);
p("Pitching %.0lf ", (Current)->player.Pitch_Rate);
p("\n---------------------------------------------------------\n");
Current = Current->next;
}
}

void FreeNodes(node **StartPtr)
{
node *Head = *StartPtr;
node *temp;
while(Head != NULL)
{
temp = Head;
Head = Head->next;
free(temp->player.Full_Name);
free(temp);
}
}

void MakeList(char* argv, struct node **StartPtr, int Limit)
{ 
char NAME[MAX_NAME] = {""};
int ID = 0;
double Bat = 0;
double Def = 0;
double Pit = 0;
int Counter = 0;

FILE *InPtr = NULL;
if(OpenFile(&InPtr, argv) ==0)
{p("\nFile failed to load at make list....");}
else
{
	while(fs(InPtr, "%s" "%d" "%lf" "%lf" "%lf", NAME, &ID, &Bat, &Def, &Pit ) != EOF && Counter < Limit)
	{
	addnode(StartPtr, NAME, ID, Bat, Def, Pit);	
	Counter++;
	}	
if(Counter < Limit){p("\nHit EOF before Limit.\nTried to list more players then available\nAll available players added.\n");}	
fclose(InPtr);
}
}

void draft(node **TeamAStart, node **TeamBStart, node **TeamCStart, node **DraftList, char* argv1, char* argv2, char* argv3, char* argv4)
{
char CurrentTeam = {'o'};
FILE *INTeamA = NULL;
FILE *INTeamB = NULL;
FILE *INTeamC = NULL;
FILE *INDraftOrder = NULL;
int ID = 0;

	if(OpenFile(&INTeamA, argv1) ==0)
	{
		p("\nTeam A failed to load at Draft List....");
	}
	else
	{
		if(OpenFile(&INTeamB, argv2) ==0)
		{
			p("\nTeam B failed to load at Draft List....");
		}
		else
		{
			if(OpenFile(&INTeamC, argv3) ==0)
			{
				p("\nTeam C failed to load at Draft List....");
			}
			else
			{
				if(OpenFile(&INDraftOrder, argv4) ==0)
				{
					p("\nDraft Order *Bonus* failed to load at Draft List....");	
				}
				else
				{
					p("\n\n\n***I DID THE BONUS!\nWITHOUT HARDCODING IT FTW!!!***\n\n\n");
					while(fs(INDraftOrder, "%c", &CurrentTeam) != EOF)
					{
						if( (CurrentTeam>='a' && CurrentTeam<='z') || (CurrentTeam>='A' && CurrentTeam<='Z'))
						{
							if(CurrentTeam == 'A' || CurrentTeam == 'a')
							{
							fs(INTeamA, "%d", &ID);
							SearchList(DraftList, TeamAStart, ID);
							}
							else
							{
								if(CurrentTeam == 'B' || CurrentTeam == 'b')
								{
									fs(INTeamB, "%d", &ID);
									SearchList(DraftList, TeamBStart, ID);
								}
								else
								{
									if(CurrentTeam == 'C' || CurrentTeam == 'c')
									{
										fs(INTeamC, "%d", &ID);
										SearchList(DraftList, TeamCStart, ID);
									}
									else
									{
										p("\n\n**** Invalid Team In Draft ****\n\n*** Team %c ***\n\n", CurrentTeam);
									}
								}
							}
						}
					}	
				}		
			}		
		}		
	}		
fclose(INTeamA);
fclose(INTeamB);
fclose(INTeamC);
fclose(INDraftOrder);	
}

int OpenFile(FILE **InPtr, char *argv)
{
int State = 1;
*InPtr = fopen(argv, "r");
if(*InPtr == NULL){p("\nFile failed to load at open..."); State = 0;}
return (State);
}

void addnode(node **StartPtr, char* NAME, int ID, double Bat, double Def, double Pit)
{
node *Utility;
node *Current;
node *Previous;

if(*StartPtr == NULL)
{
*StartPtr = malloc(sizeof(node));
(*StartPtr)->player.Full_Name = strdup(NAME);
(*StartPtr)->player.Player_ID = ID;
(*StartPtr)->player.Batting_Rate = Bat;
(*StartPtr)->player.Defense_Rate = Def;
(*StartPtr)->player.Pitch_Rate = Pit;
(*StartPtr)->next = NULL;
}
else
{
Current = (*StartPtr);
while(Current != NULL)
{
Previous = Current;
Current = Current->next;
}
Utility = malloc(sizeof(node));
Utility->player.Full_Name = strdup(NAME);
Utility->player.Player_ID = ID;
Utility->player.Batting_Rate = Bat;
Utility->player.Defense_Rate = Def;
Utility->player.Pitch_Rate = Pit;
Utility->next = NULL;
Previous->next = Utility;

}
}

double Average(node *Team)
{
	node *Current;
	double Total = 0;
	double Average = 0;
	
	Current = Team;
	while(Current != NULL)
	{
		Total = ((Current->player.Batting_Rate) + (Current->player.Defense_Rate) + (Current->player.Pitch_Rate) + Total);
		Current = Current->next;
	}
	
	Average = (Total/3);
	
	return (Average);
}

void WhoWon(node *TeamAStart, node *TeamBStart, node *TeamCStart)
{
double	TA = Average(TeamAStart);
double TB = Average(TeamBStart);
double TC = Average(TeamCStart);

	if(TA == TB && TA == TC)
	{
		//three way tie
		p("\n\n ***THREE WAY TIE, ALL TEAMS EQUAL***");
	}
	else
	{
		if(TA > TB && TA > TC)
		{
			//A wins
			p("\n\n ***TEAM A IS VICTORIOUS, ALL HAIL TEAM A!***");
		}
		else
		{
			if(TA == TB && TA > TC)
			{
				//A & B tie
				p("\n\n ***TEAM A AND TEAM B TIE, TEAM C HAS FAILED!***");
			}
			else
			{
				if(TA > TB && TA == TC)
				{
					//A & C tie
					p("\n\n ***TEAM A AND TEAM C TIE, TEAM B IS FIRED!***");
				}
				else
				{
					if(TB > TC && TB > TA)
					{
						//B wins
						p("\n\n ***TEAM B IS VICTORIOUS, TEAM B IS STRONGEST!***");
					}
					else
					{
						if(TB == TC && TB > TA)
						{
							//B & C Tie
							p("\n\n ***TEAM B AND TEAM C HAVE WON THE DAY, TEAM A HAS FALLEN!***");
						}
						else
						{
							if(TC > TA && TC > TB)
							{
								//C wins
								p("\n\n ***TEAM C IS VICTORIOUS, REALLY?!***");
							}
							else
							{
							p("\n\n**** FATAL ERROR ****\n\n");
							}
						}
					}
				}
			}
		}
	}

p("\n\n");
}
