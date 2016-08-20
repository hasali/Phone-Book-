#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook.h"


/* 
 * FILE NAME: main.c
 * 
 * AUTHOR: Alissa Nonato and Hassan Mahmood
 *
 * DESCRIPTION: This phone book application allows the user to add,
 * retrieve, delete and sort records in a phone book. The user can
 * also load the phone book records from a file and save any
 * changes made.
 * 
*/


void mainMenu();
void sort(PhoneRec pr);
void addRecord(PhoneRec pr);
void load(PhoneRec pr);


//Initializes PhoneRec array, loads text file, and loads main options.
int main(void)
{
	PhoneRec pr = initPhoneRec();
	loadRec(pr);
	printf("Welcome to Our Phone Book Application\n\n");
	mainMenu(pr);

	return 0;
}


//Method for displaying options which load other functions
void mainMenu(PhoneRec pr)
{
	int input;
	
	printf("0. Print Phone Records\n");
	printf("1. Add Record\n");
	printf("2. Retrieve Record\n");
	printf("3. Delete Record\n");
	printf("4. Load File\n");
	printf("5. Save To File\n");
	printf("6. Sort\n");
	printf("7. Exit\n\n");

	do
	{
		printf("Choose an option: \n");
		scanf("%d", &input);
	}while((input < 0 || input > 7) && cleanInput());


	if(input == 0)
	{
		printf("\n");
		printRec(pr);
		mainMenu(pr);
	}
	else if(input == 1)
	{
		addRecord(pr);
		mainMenu(pr);
	}
	else if(input == 2)
	{
		retrieveRec(pr);
		mainMenu(pr);
	}
	else if(input == 3)
	{
		deleteRec(pr);
		mainMenu(pr);
	}
	else if(input == 4)
	{
		load(pr);
		mainMenu(pr);
	}
	else if(input == 5)
	{
		saveRec(pr);
		printf("\nState saved!\n\n");
		mainMenu(pr);
	}
	else if(input == 6)
	{
		sort(pr);
		mainMenu(pr);
	}
	else if(input == 7)
	{
		char in;
		do
		{
			printf("\nDo you want to save current state(y/n): ");
			scanf("%s", &in);
		
			if(in == 'y')
			{
				saveRec(pr);
				printf("State saved!\n");
				exit(0);
				
			}
			else if(in == 'n')
			{
				printf("\nGo Dive In A Snow Pile\n");
				exit(0);	
			}
			else
				printf("Invalid Input!\n");
				
			
		}while(in);	
	}	
}


//Adds user input into records which is added to the PhoneRec array.
void addRecord(PhoneRec pr)
{
	
	char first[MaxNL+1]; 
	char last[MaxNL+1]; 
	char pnum[11]; 
	char in = 'y';
	
		
	while(in != 'n')
	{
		do
		{
			printf("\nEnter First Name: ");
			scanf("%s", first); 
		}while(!isChar(first));
		
		do
		{
			printf("Enter Last Name: ");
			scanf("%s", last);
		}while(!isChar(last));
		do
		{
			printf("Enter Phone Number: ");
			scanf("%s", pnum);
			if(!isNum(pnum))
				printf("\nMust be Numbers only\n\n");
			else if(strlen(pnum) !=10)
				printf("\nPhone number must be 10 numbers long.\n\n");
			else if(checkDupNum(pr,pnum))
				printf("\nPhone number already exists.\n\n");
		}while(checkDupNum(pr,pnum) || !isNum(pnum) || strlen(pnum) !=10);

		Record r = initRec(firstCap(first), firstCap(last), pnum);	
		addRec(pr,r);
		quicksort(pr->phoneRec, 0, pr->recIndex-1, 'f');

		do
		{
			printf("\nDo you want to add another record? (y/n)");
			scanf("%s", &in);
			if(in=='y')
				break;
			else if(in=='n')
			{
				printf("\n");			
				mainMenu(pr);
			}
			else
				printf("Enter valid input\n\n");
		}while(in);	
	}
	
}


//Prompts user to choose a sort criteria. Calls quicksort accordingly.
void sort(PhoneRec pr)
{
	char in[11];
	do
	{
		printf("\nSort by First Name(f), Last Name(l), or Phone Number(p)?\n");
		scanf("%s", in);
		printf("\n");
		firstCap(in);
		if(!strcmp(in, "F"))
		{
			quicksort(pr->phoneRec,0, pr->recIndex-1,'f');	
			printRec(pr);
			printf("Sorted by First Name\n\n");
			mainMenu(pr);
		}
		
		else if(!strcmp(in, "L"))
		{
			quicksort(pr->phoneRec,0, pr->recIndex-1,'l');
			printRec(pr);
			printf("Sorted by Last Name\n\n");
			mainMenu(pr);
		}
		else if(!strcmp(in, "P"))
		{
			quicksort(pr->phoneRec,0, pr->recIndex-1,'p');
			printRec(pr);
			printf("Sorted by Phone Number\n\n");
			mainMenu(pr);
		}
		else
		{
			printf("Invalid input\n");			
		}
	}while((strcmp(in,"F") || strcmp(in,"L") || strcmp(in,"P")));
		
}


//Calls loadRec and prints success statement.
void load(PhoneRec pr)
{	
		
	loadRec(pr);
	printf("Load Successful\n\n");
}
