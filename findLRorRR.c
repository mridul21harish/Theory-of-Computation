#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define size 10

int main()
{
	char nonterminals;
	char alpha; char beta;
	int number;
	char production[10][size];
	int index = 3;
	
	printf("Enter the number of productions of the grammar : ");
	scanf("%d", &number);
	printf("\n");
	
	printf("\nRules of entry : Enter the grammar as S->A|a\n"); 
	printf("Epsilon production is denoted by '#' symbol\n");
	
	for(int i = 0; i < number; i = i+1)
	{
		printf("Enter production no. %d :  ", i);
		scanf("%s", production[i]);
	}
	
	for(int i = 0; i < number; i = i+1)
	{
		int flag = 0;
		printf("\nGrammar : %s", production[i]);
		nonterminals = production[i][0];
		
		if(nonterminals == production[i][index])
		{
			printf(" is a left recursive grammar\n");
			flag = 1;
			continue;
		}
		
		while(1)
		{
			if(production[i][index + 1] == '\0')
			{	
				break;
			}
			if(production[i][index] == '|')
			{
				if(production[i][index + 1] == nonterminals)
				{
					printf(" is left recursive\n");
					flag = 1;
					break;
				}
			}
			index = index + 1;
		}
		
		if(flag == 0)
		{
			int flag_1 = 0;
			index = 0;
			while(1)
			{
				if((production[i][index + 1] == '|' || production[i][index + 1] == '\0'))
				{
					if(production[i][index] = nonterminals)
					{
						printf(" is right recursive\n");
						flag_1 = 1;
						break;
					}
					if(production[i][index + 1] == '\0')
						break;
				}
				index = index + 1;
			}
			if(flag_1 == 0)
			{
				printf(" is neither left recursive nor right recurseive\n");
			}
		}
	}
	printf("\n");
}	


