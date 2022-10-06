#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int n = 1; int i = 0; int j = 0; int k = 0;
char production[10][10];

int main()
{
	int i = 0; int z;
	char c; char ch; 
	
	printf("\nRules of entry : Enter the grammar as S=A|a\n"); 
	printf("Epsilon production is denoted by '#' symbol\n");
	
	printf("Enter the production : ");
	for(i = 0; i < n; i = i+1)
	{
		scanf("%s%c", production[i], &ch);
	}
	
	c = production[0][0];
	if(production[0][2] == c)
	{
		printf("Left recursion is found\n");
		printf("%c'->", c);
		
		for(k = 3; k < strlen(production[0]) && production[0][k] != '|'; k = k+1)
		{
			printf("%c", production[0][k]);
		}
		printf("%c'|e", c);
		n = k; i = 0;
		printf("\n%c->", c);
		
		for(k = n+1; k < strlen(production[0]) && production[0][k] != '\0'; k = k+1)
		{
			printf("%c", production[0][k]);
		}
		printf("%c'", c);
		printf("\n");
	}
	else
	{
		printf("There is no left recursion\n");
	}
	return 0;
}
