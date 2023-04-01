#include<cfss.h>
#include<user.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

CFSS *headCFSS = NULL;
CFSS *tailCFSS = NULL;

void addCfss(int uid)
{
	CFSS *newCfs = NULL;
	newCfs = (CFSS *)malloc(sizeof(CFSS));
	if(newCfs == NULL)
	{
		printf("\nMemory Allocation failed!");
		exit(EXIT_SUCCESS);
	}
	newCfs->uId = uid;
	newCfs->next = NULL;
	if(headCFSS == NULL)
	{
		headCFSS = newCfs;
		tailCFSS = newCfs;
	}
	else
	{
		tailCFSS->next = newCfs;
		tailCFSS = newCfs;
	}
}

void loadCfss()
{
	FILE *fptr = NULL;
	CFSS temp;
	CFSS *newCfs = NULL;
	int flag = 0;

	fptr = fopen("../data/cfs.dat","r");
	if(fptr == NULL)
	{
		perror("fopen()");
		exit(EXIT_FAILURE);
	}
	while(readCfsFile(fptr,&temp))
	{
		if(flag == 0)
		{
			newCfs = (CFSS *)malloc(sizeof(CFSS));
			if(newCfs == NULL)
			{
				printf("\nMemory Allocation failed!");
				exit(EXIT_FAILURE);
			}
			newCfs->uId = temp.uId;
			newCfs->cfsNumber = temp.cfsNumber;
			newCfs->cfsActive = temp.cfsActive;
			strcpy(newCfs->serviceType,temp.serviceType);
			newCfs->next = NULL;
			headCFSS = newCfs;
			tailCFSS = newCfs;
			flag = 1;
			continue;
		}
		newCfs = (CFSS *)malloc(sizeof(CFSS));
		if(newCfs == NULL)
		{
			printf("\nMemory Allocation failed");
			exit(EXIT_FAILURE);
		}
		newCfs->uId = temp.uId;
		newCfs->cfsNumber = temp.cfsNumber;
		newCfs->cfsActive = temp.cfsActive;
		strcpy(newCfs->serviceType,temp.serviceType);
		newCfs->next = NULL;
		tailCFSS->next = newCfs;
		tailCFSS = newCfs;
	}
	fclose(fptr);
}

int readCfsFile(FILE *fptr,CFSS *temp)
{
	int ret = fread(temp,sizeof(CFSS),1,fptr);

	return ret;
}

void writeCfss()
{
	CFSS *temp = headCFSS;
	FILE *fptr = NULL;
	int retVal = 0;

	fptr = fopen("../data/cfs.dat","w");
	if(fptr == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while(temp != NULL)
	{
		retVal = writeCfsFile(FILE *fptr,CFSS *temp);
		if(retVal == 0)
		{
			perror(write);
			exit(EXIT_FAILURE);
		}
		temp = temp->next;
	}
	fclose(fptr);
}

int writeCfsFile(FILE *fptr,CFSS *temp)
{
	if(temp == NULL)
	{
		return 0;
	}
	fseek(fptr,0,SEEK_END);
	temp->next = NULL;
	int ret = fwrite(temp,sizeof(CFSS),1,fptr);
	return ret;
}

void activateCfss(int uId,int cfsNumber,char *serviceType)
{
	CFSS *temp = headCFSS;

	while(temp != NULL)
	{
		if(temp->uId == uId)
		{
			temp->cfsNumber = cfsNumber;
			temp->cfsActive = 1;
			strcpy(temp->serviceType,serviceType)
			printf("\nCall forwarding Service Activated successfully!");
			break;
		}
		temp = temp->next;
	}
}

void deactivateCfss(int uId)
{
	CFSS *temp = headCFSS;

	while(temp != NULL)
	{
		if(temp->uId == uId)
		{
			if(temp->cfsActive != 0)
			{
				temp->cfsActive = 0;
				temp->cfsNumber = 0;
				memset(temp->serviceType,'\0',MAX_BUFF);
				break;
			}
			else
			{
				printf("\nYou don't have any activated service!");
				break;
			}
		}
	}
}

void unregister(int uId)
{
	UD *userTemp = headUD;
	CFSS *cfsTemp = headCFSS;
	UD *userPrev = NULL;
	CFSS *cfsTemp = NULL;

