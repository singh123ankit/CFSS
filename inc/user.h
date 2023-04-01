#ifndef USER_H
#define USER_H

#define MAX_BUFF 1024

struct userDetails
{
	char fName[MAX_BUFF];
	char lName[MAX_BUFF];
	char gender;
	long int pNumber;
	char uName[MAX_BUFF];
	int uId;
	char passwd[MAX_BUFF];
	struct userDetails *next;
};

typedef struct userDetails UD;

extern UD *headUD ;
extern UD *tailUD ;

void getPDetails(UD *);
void loadPDetails();
int readUserFile(FILE *,UD *);
void writePDetails();
int writeUserFile(FILE *,UD *);

#endif

