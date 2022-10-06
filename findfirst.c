#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int production_count; //counting the number of productions
char production[30][30]; //productions of the grammar
char nonterminals[10]; //non terminals of the grammar
char unique_nonterminals[10]; //non terminals remaining after removing duplicates
char terminals[10]; //terminals of the grammar
char first[20]; //first of the non terminals
int first_count; //counting the number of first of non terminals
int previous_row; int previous_coloumn; //they store row and coloumn of previously called first
int nonterminals_count; //counting the number of non terminals of the grammar

void findfirst(char c, int val, int flag); //function to find first of the non terminals
void duplicate_removal(); //function to remove duplicate non terminals

int main()
{
	int i = 0; int j = 0; int flag = 0;
	first_count = 0;
	
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
	
	duplicate_removal();
	printf("\n");
	
	/*for(int k = 0; k < nonterminals_count; k = k+1)
	{
		printf("%c\n",unique_nonterminals[k]);
	}*/
	
	for(int k = 0; k < nonterminals_count; k = k+1)
	{
		findfirst(unique_nonterminals[k], 0, 0);
		printf("First of %c is :", unique_nonterminals[k]);
		
		for(i = 0; i < first_count; i = i+1)
		{
			if(k == 0 && first[i] == '#')
				continue;
			else
				printf("%c ", first[i]);
		}
		
		memset(first, 0, 20);
		first_count = 0;
		printf("\n");
	}
	
	printf("\n");
	return 0;
}

void findfirst(char c, int val, int flag)
{
	int i; int j;
	//char res[20];
	int production_index = 0;
	
	if(c != '#')
	{
		for(i = 0; i < production_count; i = i+1)
		{
			if(production[i][0] == c) //this checks if the symbol is a non terminal
			{
				production_index = i;
				val = 0;
				
				if(i == 0)
				{
					findfirst(production[production_index][val + 3], val, 0);
				}
				else
				{
					findfirst(production[production_index][val + 3], val, 1);
				}
				
				previous_row = production_index;
				previous_coloumn = 3 + val;
			}
			else //if the symbol is a terminal
			{
				if(!strchr(first, c) && !strchr(unique_nonterminals, c)) //this checks if not already in the set and not a non terminal
				{
					first[first_count] = c;
					first_count = first_count + 1;
				}
			}
		}
	}
	else if(flag == 1) //if it is an indirect null from the first of other variabls
	{
		if(!strchr(first, c))
		{
			first[first_count] = c;
			first_count = first_count + 1;
		}
		
		val = val + 1;
		previous_coloumn = previous_coloumn + val;
		char d = production[previous_row][previous_coloumn + 3];
		findfirst(d, val, 1);
	}
	else //if it is a direct null of starting variable
	{
		val = val + 1;
		previous_coloumn = previous_coloumn + val;
		char d = production[previous_row][previous_coloumn + 3];
		findfirst(d, val, 1);
	}
}

void duplicate_removal()
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
