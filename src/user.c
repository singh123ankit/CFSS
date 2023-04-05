/****************************************************************************************************
 * FILE NAME    : user.c
 *
 * DESCRIPTION  : This file contains function to perform user call forwarding operation
 *
 *******************************************************************************************************/

/*******************************************************************************************************
*                           HEADER FILES
*********************************************************************************************************/

#include<user.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<cfss.h>

UD *headUD = NULL;
UD *tailUD = NULL;
CFSS *headCFSS = NULL;
CFSS *tailCFSS = NULL;


/*******************************************************************
 * FUNCTION NAME: getPDetails()
 *
 * DESCRIPTION: This function is used get user details, and 
 * 		stores in the linked list.	
 *
 * RETURNS      :  returns SUCCESS or FAILURE
 *******************************************************************/
UD *getPDetails()
{
	UD *newUser = NULL;
	char fName[MAX_BUFF] = {'\0',};
	char lName[MAX_BUFF] = {'\0',};
	char passwd[MAX_BUFF] = {'\0',};
	char uName[MAX_BUFF] = {'\0',};
	char gender = '\0';
	long int pNumber = 0;


	newUser = (UD *)malloc(sizeof(UD));
	if(newUser == NULL)
	{
		printf("\nMemory Allocation failed!");
		exit(EXIT_FAILURE);
	}
	printf("\nEnter First Name: ");
	scanf(" ");
	fgets(fName,MAX_BUFF,stdin);
	fName[strlen(fName)-1] = '\0';
	printf("\nEnter Last Name: ");
	scanf(" ");
	fgets(lName,MAX_BUFF,stdin);
	lName[strlen(lName)-1] = '\0';
	printf("\nEnter User Name: ");
	scanf(" ");
	fgets(uName,MAX_BUFF,stdin);
	uName[strlen(uName)-1] = '\0';
	printf("\nEnter Gender(M/F): ");
	scanf(" ");
	scanf("%c",&gender);
	printf("\nEnter Phone Number: ");
	scanf("%ld",&pNumber);
	printf("\nEnter Password: ");
	scanf(" ");
	fgets(passwd,MAX_BUFF,stdin);
	passwd[strlen(passwd)-1] = '\0';

	strcpy(newUser->fName,fName);
	strcpy(newUser->lName,lName);
	strcpy(newUser->uName,uName);
	strcpy(newUser->passwd,passwd);
	newUser->gender = gender;
	newUser->pNumber = pNumber;
	newUser->next = NULL;
	return newUser;
}
/*******************************************************************
 * FUNCTION NAME: loadPDetails()
 *
 * DESCRIPTION: This function is used to load data from user 
 * 		database and puts in the linked list.
 *
 * RETURNS      :  returns SUCCESS or FAILURE
 *******************************************************************/
void loadPDetails()
{
	FILE *fptr = NULL;
	UD  temp;
	UD *newUser = NULL;
	int flag = 0;

	fptr = fopen("/home1/trainee59/CFSS/data/user.dat","r");
	if(fptr == NULL)
	{
		perror("fopen()");
		exit(EXIT_FAILURE);
	}
	while(readUserFile(fptr,&temp))
	{
		if(flag == 0)
		{
			newUser = (UD *)malloc(sizeof(UD));
			if(newUser == NULL)
			{
				printf("\nMemory allocation failed!");
				exit(EXIT_FAILURE);
			}
			strcpy(newUser->fName,temp.fName);
			strcpy(newUser->lName,temp.lName);
			strcpy(newUser->passwd,temp.passwd);
			strcpy(newUser->uName,temp.uName);
			newUser->uId = temp.uId;
			newUser->gender = temp.gender;
			newUser->pNumber = temp.pNumber;
			newUser->next = NULL;
			headUD = newUser;
			tailUD = newUser;
			flag = 1;
			continue;
		}
		newUser = (UD *)malloc(sizeof(UD));
		if(newUser == NULL)
		{
			printf("\nMemory allocation failed!");
			exit(EXIT_FAILURE);
		}
		strcpy(newUser->fName,temp.fName);
		strcpy(newUser->lName,temp.lName);
		strcpy(newUser->passwd,temp.passwd);
		strcpy(newUser->uName,temp.uName);
		newUser->uId = temp.uId;
		newUser->gender = temp.gender;
		newUser->pNumber = temp.pNumber;
		newUser->next = NULL;
		tailUD->next = newUser;
		tailUD = newUser;
	}
	fclose(fptr);
}


/*******************************************************************
 * FUNCTION NAME: readUserFile()
 *
 * DESCRIPTION: This function is used to read user data.
 *
 * RETURNS      :  returns SUCCESS or FAILURE
 *******************************************************************/

int readUserFile(FILE *fptr, UD *temp)
{
	int ret = fread(temp, sizeof(UD),1,fptr);

	return ret;
}
/*******************************************************************
 * FUNCTION NAME: writePDetails()
 *
 * DESCRIPTION: This function is used to write user details to user 
 * 		database.
 *
 * RETURNS      :  returns SUCCESS or FAILURE
 *******************************************************************/

void writePDetails()
{
	UD *temp = headUD;
	FILE *fptr = NULL;
	int retVal = 0;
	
	fptr = fopen("/home1/trainee59/CFSS/data/user.dat","r+");
	if(fptr == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while(temp != NULL)
	{
		retVal = writeUserFile(fptr,temp);
		if(retVal == 0)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		temp = temp->next;
	}
	fclose(fptr);
}

/*******************************************************************
 * FUNCTION NAME: writeUserDetails()
 *
 * DESCRIPTION: This function is used to write data from the 
 * 		linked list and stores them to the file.
 *
 * RETURNS      :  returns SUCCESS or FAILURE
 *******************************************************************/

int writeUserFile(FILE *fptr,UD *temp)
{
	if(temp == NULL)
	{
		return 0;
	}

	if(ftell(fptr)!=0)
	fseek(fptr,0,SEEK_END);
	
	int ret = fwrite(temp, sizeof(UD),1,fptr);
	return ret;
}
