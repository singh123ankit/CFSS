#include<user.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

UD *headUD = NULL;
UD *tailUD = NULL;

void getPDetails(UD *newUser)
{
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
	scanf("%d",&age);
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
}

void loadPDetails()
{
	FILE *fptr = NULL;
	UD  temp;
	UD *newUser = NULL;
	int flag = 0;

	fptr = fopen("../data/user.dat","r");
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

int readUserFile(FILE *fptr, UD *temp)
{
	int ret = fread(temp, sizeof(UD),1,fptr);

	return ret;
}

void writePDetails()
{
	UD *temp = headUD;
	FILE *fptr = NULL;
	int retVal = 0;
	
	fptr = fopen("../data/user.dat","w");
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

int writeUserFile(FILE *fptr,UD *temp)
{
	if(temp == NULL)
	{
		return 0;
	}
	fseek(fptr,0,SEEK_END);
	temp->next = NULL;
	int ret = fwrite(temp, sizeof(UD),1,fptr);
	return ret;
}
