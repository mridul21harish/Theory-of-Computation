#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int production_count; //counting the number of productions
char production[30][30]; //productions of the grammar
char nonterminals[10];  //non terminals of the grammar
char unique_nonterminals[10]; //non terminals of the grammar after removing duplicates
char terminals[10]; //terminals of the grammar
char first[20]; //first of the grammar
int first_count; //counting the number of first
char follow[20]; //follow of the grammar
int follow_count; //counting the number of follow
int previous_row; int previous_coloumn; //they store row and coloumn of previously called first
int nonterminals_count; //counting the number of non terminals 

void duplicateremoval_first(); //function to remove duplicate non terminals for first
void duplicateremoval_follow();//function to remove duplicate non terminals for follow
int findfirst_for_follow(char c, int val); //function to find first of the non terminals
void findfollow(char c); //function to find follow 

int main()
{
	int i = 0; int j = 0; 
	
	printf("\nRules of entry : If there are multiple entries in the same production, split and enter them\n"); 
	printf("Eg : S->A|B|C == S->A and S->B and S->C\n");
	printf("Epsilon production is denoted by '#' symbol\n");
	
	printf("Enter the number of productions : ");
	scanf("%d", &production_count);
	printf("\n");
	
	for(i = 0; i < production_count; i = i+1)
	{
		printf("Enter production no. %d :  ", i);
		scanf("%s", production[i]);
		nonterminals[nonterminals_count] = production[i][0];
		nonterminals_count = nonterminals_count + 1;
	}
	
	duplicateremoval_first();
	printf("\n");
	
	for(int k = 0; k < nonterminals_count; k = k+1)
	{
		findfollow(unique_nonterminals[k]);
		printf("Follow of %c is :", unique_nonterminals[k]);
		duplicateremoval_follow();
		for(i = 0; i < strlen(follow); i = i+1)
		{
			printf("%c ", follow[i]);
		}
		
		memset(first, 0, 20);
		follow_count = 0;
		printf("\n");
	}
	
	printf("\n");
	return 0;
}

void duplicateremoval_first()
{
	int index = 0;
	
	for(int i = 0; i < nonterminals_count; i = i+1)
	{
		int j;
		for(j = 0; j < i; j = j+1)
		{
			if(nonterminals[i] == nonterminals[j])
			{
				break;
			}
		}
		
		if(j == i)
		{
			unique_nonterminals[index++] = nonterminals[i];
		}
	}
	nonterminals_count = index;
}

void duplicateremoval_follow()
{
	for(int i = 0; i < strlen(follow); i = i+1)
	{
		for(int j = i+1; follow[j] != '\0'; j = j+1)
		{
			if(follow[j] == follow[i])
			{
				for(int k = j; follow[k] != '\0'; k = k+1)
				{
					follow[k] = follow[k+1];
				}
			}
		}
	}
}

int findfirst_for_follow(char c, int val)
{
	int i; int j;
	int null = 0; //null = 1 when first contains epsilon
	int production_index = 0;
	
	if(c != '#') //when not a null
	{
		for(i = 0; i < production_count; i = i+1)
		{
			if(production[i][0] == c) //this checks if the symbol is a non terminal
			{
				production_index = i;
				val = 0;
				findfirst_for_follow(production[production_index][val + 3], val);
				previous_row = production_index;
				previous_coloumn = val + 3;
			}
			else //this is if the symbol is a terminal
			{
				if(!strchr(first, c) && !strchr(nonterminals, c)) //this checks if not already in the set and not a non terminal
				{
					char x[] = " ";
					x[0] = c;
					strcat(first, x);
				}
			}
		}
	}
	else //when is null
	{
		null = 1;
		val = val + 1;
		previous_coloumn = previous_coloumn + val;
		char d = production[previous_row][previous_row + 3];
		findfirst_for_follow(d, val);
	}
	return null;
}

void findfollow(char c)
{
	int i; int j;
	
	for(i = 0; i < production_count; i = i+1)
	{
		for(j = 3; production[i][j] != '\0'; j = j+1)
		{
			if(production[i][j] == c)
			{
				if(production[i][j+1] != '\0') //if it is not at the last of production
				{
					int val = 1;
					while(1)
					{
						int null = findfirst_for_follow(production[i][j + val], 0);
						if(null == 1)
						{
							val = val + 1;
						}
						else
						{
							break;
						}
					}
					strcat(follow, first);
				}
				else
				{
					findfollow(production[i][0]); //if it is last then find follow of LHS
				}
			}
		}
	}
	
	if(production[0][0] == c)
	{
		if(!strchr(first, '$'))
		{
			strcat(follow, "$");
			follow_count = follow_count + 1;
		}
	}
}
	
