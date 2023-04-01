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


void addCfss(int);
void loadCfss();
int readCfsFile(FILE *,CFSS *);
void writeCfss();
int writeCfsFile(FILE *,CFSS *);
void activateCfss(int,int,char *);
void deactivateCfss(int);
void makeCall(int);

#endif
