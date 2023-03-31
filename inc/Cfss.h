#ifndef CFSS_H
#define CFSS_H

#define MAX_BUFF 1024

struct callForwarding
{
	int uId = 0;
	long int cfsNumber = 0;
	int cfsActive = 0;
	char serviceType[MAX_BUFF] = {'\0'};
	struct callForwarding *next;
}CFSS;

typedef struct CallForwarding CFSS;

extern CFSS *headCFSS;
extern CFSS *tailCFSS;


void addCfss(int uid);
void loadCfss();
int readCfsFile(FILE *fptr,CFSS *temp);
void writeCfss();
int writeCfsFile(FILE *fptr,CFSS *temp);
void updateCfss(int cfsNumber,int cfsActive,char *serviceType);

#endif
