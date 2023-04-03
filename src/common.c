#include<common.h>
#include<user.h>
#include<cfss.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


void signUp()
{
	UD *newUser = NULL;

	newUser = getPDetails();
	if(headUD == NULL)
	{
		newUser->uId = 1;
		headUD = newUser;
		tailUD = newUser;
	}
	else
	{
		newUser->uId = (tailUD->uId) + 1;
		tailUD->next = newUser;
		tailUD = newUser;
	}
	addCfss(newUser->uId);
	printf("\nYou have been registered successfully!\n\n");
}

int signIn()
{
	char uName[MAX_BUFF] = {'\0',};
	char passwd[MAX_BUFF] = {'\0',};
	int uid = 0;

	printf("\nEnter User Name: ");
	scanf(" ");
	fgets(uName,MAX_BUFF,stdin);
	uName[strlen(uName)-1] = '\0';
	printf("\nEnter Password: ");
	scanf(" ");
	fgets(passwd,MAX_BUFF,stdin);
	passwd[strlen(passwd)-1] = '\0';
	uid = checkCred(uName,passwd);
	if(uid > 0)
	{
		printf("\nLogged In Successfully!\n\n");
		return uid;
	}
	printf("\nEither User Name or Password is Incorrect!Try Again.\n\n");
	return -1;
}

int checkCred(char *uName,char *passwd)
{
	int flag = 0;
	int uid = 0;
	UD *temp = headUD;


	while(temp != NULL)
	{
		if(strcmp(temp->uName,uName) == 0)
		{
			flag += 1;
			if(strcmp(temp->passwd,passwd) == 0)
			{
				flag += 1;
				uid = temp->uId;
				break;
			}
			else
			{
				break;
			}
		}
		temp = temp->next;
	}
	if(flag == 2)
	{
		return uid;
	}
	return 0;
}

int initialScreen()
{
	int choice = 0;

	system("clear");
	printf("*******************Welcome To Call Forwarding System Simulator*********************");
	printf("\n\n");
	printf("Press,");
	printf("\n1. To SignUp");
	printf("\n2. To SignIn");
	printf("\n3. To Exit");
	printf("\n");
	printf("***********************************************************************************");
	printf("\nEnter your choice: ");
	scanf("%d",&choice);
	return choice;
}

int mainScreen(char *fName)
{
	int choice = 0;

	system("clear");
	printf("***********************Welcome\t\t%s****************************",fName);
	printf("\n\n");
	printf("Press,");
	printf("\n1. To Activate Call Forwarding Service");
	printf("\n2. To Deactivate Call Forwarding Service");
	printf("\n3. To Unregister");
	printf("\n4. Make a call");
	printf("\n5. Log Out");
	printf("\n6. Exit Application");
	printf("\n");
	printf("****************************************************************");
	printf("\nEnter your choice: ");
	scanf("%d",&choice);
	return choice;
}

int cfsScreen()
{
	int choice = 0;

	system("clear");
	printf("Press,");
	printf("\n1. Unconditional");
	printf("\n2. No Reply");
	printf("\n3. Busy");
	printf("\n\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}

void  searchUser(int uid,char *fName)
{
	UD *temp = headUD;

	while(temp != NULL)
	{
		if(temp->uId == uid)
		{
			strcpy(fName,temp->fName);
			break;
		}
		temp = temp->next;
	}
}


