/****************************************************************************************************
 * FILE NAME    : user.c
 *
 * DESCRIPTION  : This file contains function to perform user call forwarding operation
 *
 *******************************************************************************************************/

/*******************************************************************************************************
*                           HEADER FILES
*********************************************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cfss.h>
#include<user.h>

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
	int flag = 1;
	int temp = 0;
	UD *newUser = NULL;
	char fName[MAX_BUFF] = {'\0',};
	char lName[MAX_BUFF] = {'\0',};
	char passwd[MAX_BUFF] = {'\0',};
	char uName[MAX_BUFF] = {'\0',};
	char gender = '\0';
	char pNumber[MAX_BUFF] = {'\0',};	




	newUser = (UD *)malloc(sizeof(UD));
	if(newUser == NULL)
	{
		printf("\nMemory Allocation failed!");
		exit(EXIT_FAILURE);
	}
	while(flag)
	{
		printf("\nEnter First Name: ");
		bzero(fName,MAX_BUFF);
		scanf(" ");
		fgets(fName,MAX_BUFF,stdin);
		fName[strlen(fName)-1] = '\0';
		temp = checkName(fName);
		if(temp != -1)
 		{
			flag = 0;
		}
	}
	temp = 0;
	flag = 1;
	while(flag)
	{
		printf("\nEnter Last Name: ");
		bzero(lName,MAX_BUFF);
		scanf(" ");
		fgets(lName,MAX_BUFF,stdin);
		lName[strlen(lName)-1] = '\0';
		temp = checkName(lName);
		if(temp != -1)
		{
			flag = 0;
		}
	}
	printf("\nEnter User Name: ");
	scanf(" ");
	fgets(uName,MAX_BUFF,stdin);
	uName[strlen(uName)-1] = '\0';
	temp = 0;
	flag = 1;
	while(flag)
	{
		printf("\nEnter Gender(M/F): ");
		scanf(" ");
		scanf("%c",&gender);
		temp=checkGender(gender);
		if(temp!=-1)
		{
			flag=0;
		}
	}
	flag = 1;
	temp = 0;
	while(flag)
	{
		printf("\nEnter Phone Number: ");
		scanf(" ");
		fgets(pNumber,MAX_BUFF,stdin);
		pNumber[strlen(pNumber)-1]='\0';
		temp=checkPhoneNumber(pNumber);
		if(temp != -1)
		{
			flag = 0;
		}
	}

	printf("\nEnter Password: ");
	scanf(" ");
	fgets(passwd,MAX_BUFF,stdin);
	passwd[strlen(passwd)-1] = '\0';

	strcpy(newUser->fName,fName);
	strcpy(newUser->lName,lName);
	strcpy(newUser->uName,uName);
	strcpy(newUser->passwd,passwd);
	newUser->gender = gender;
	strcpy(newUser->pNumber,pNumber);
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

	fptr = fopen("/home2/trainee63/GROUP1/CFSS/data/user.dat","r");
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
			strcpy(newUser->pNumber,temp.pNumber);
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
		strcpy(newUser->pNumber,temp.pNumber);
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
	
	fptr = fopen("/home2/trainee63/GROUP1/CFSS/data/user.dat","r+");
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

int checkName(char *n) 
{
    if (n == NULL) {
        return 0;
    }
    int flag = 0;
    for (int i = 0; i < strlen(n); i++) {
        if (!isalpha(n[i])) {  
            printf("Name should contain only letters,no digits or special characters allowed\n");
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        return -1;
    return 1;
}

int checkGender(char ch)
{
    if(ch=='M'||ch=='F'||ch=='m'||ch=='f'){
        return 0;

    }

    printf("Gender can be either M or F.\n") ;
    return -1;
}

int checkPhoneNumber(char *phone) 
{
    /* to check whether phone number is 10 digits*/
    if (strlen(phone) != 10) {
        printf("Phone number should be of 10 digits only\n");
        return -1;
    }

/*to check whether no other characters are present*/
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            printf("Phone number should not have any characters\n");
            return -1;
        }
    }


    return 0;
}
