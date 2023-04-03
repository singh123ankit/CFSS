#include<common.h>
#include<cfss.h>
#include<user.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
	int choice = 0;
	int flag = 1;
	int ch = 1;
	int uid = 0;
	long int number = 0;
	char uName[MAX_BUFF];

	loadPDetails();
	loadCfss();
	while(1)
	{
		switch(initialScreen())
		{
			case 1:
				signUp();
				sleep(2);
				break;
			case 2:
				uid = signIn();
				sleep(2);
				if(uid == -1)
				{
					continue;
				}
				else
				{
					searchUser(uid,uName);
					while(flag)
					{
						choice = mainScreen(uName);
						switch(choice)
						{
							case 1:
								printf("\nEnter Call Forwarding Number: ");
								scanf("%ld",&number);	
								ch=1;
								while(ch)
								{
									choice = cfsScreen();
									if(choice == 1)
									{
										
										activateCfss(uid,number,"Unconditional");
										ch = 0;
									}
									else if(choice == 2)
									{
										activateCfss(uid,number,"No Reply");
										ch = 0;
									}
									else if(choice == 3)
									{
										activateCfss(uid,number,"Busy");
										ch = 0;
									}
									else
									{
										printf("\nEnter correct choice!");
									}
								}
								sleep(2);
								break;
							case 2:
								deactivateCfss(uid);
								sleep(5);
								break;
							case 3:
								unregister(uid);
								sleep(2);
								uid = 0;
								flag = 0;
								break;
							case 4:
								makeCall(uid);
								sleep(2);
								break;
							case 5:
								uid = 0;
								flag = 0;
								printf("\nLogged Out Successfully!\n\n");
								sleep(2);
								break;
							case 6:
								writePDetails();
								writeCfss();
								exit(0);
							default:
								printf("\nInvalid Choice!Try Again\n\n");
						}
					}
				}
				break;
			case 3:
				writePDetails();
				writeCfss();
				exit(0);
			default:
				printf("\nInvalid Choice!\n\n");
		}
	}
	return 0;
}

