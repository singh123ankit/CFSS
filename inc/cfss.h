#ifndef CFSS_H
#define CFSS_H

#include<stdio.h>
#define MAX_BUFF 1024

typedef struct callForwarding
{
	int uId;
	long int cfsNumber;
	int cfsActive;
	char serviceType[MAX_BUFF];
	struct callForwarding *next;
}CFSS;


 CFSS *headCFSS = NULL;
 CFSS *tailCFSS = NULL;


void addCfss(int);
void loadCfss();
int readCfsFile(FILE *,CFSS *);
void writeCfss();
int writeCfsFile(FILE *,CFSS *);
void activateCfss(int,int,char *);
void deactivateCfss(int);
void unregister(int);
void makeCall(int);

#endif
