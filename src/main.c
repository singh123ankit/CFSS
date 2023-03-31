#include<common.h>
#include<user.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main()
{
	//int choice = 0;
	int flag = 1;
	int uid = 0;
	long int number = 0;
	char uName[MAX_BUFF];

	loadPDetails();
	while(1)
	{
		switch(initialScreen)
		{
			case 1:
				signUp();
				break;
			case 2:
				uid = signIn();
				if(uid == -1)
				{
					continue;
				}
				else
				{
					//strcpy(uName,searchUser(uid));
					while(flag)
					{
						choice = mainScreen(uName);
						switch(choice)
						{
							case 1:
								printf("\nEnter Call Forwarding Number: ");
								scanf("%ld",&number);	
								while(ch)
								{
									choice = cfsScreen();
									if(choice == 1)
									{
										ch = 0;
									}
									else if(choice == 2)
									{
										ch = 0;
									}
									else if(choice == 3)
									{
										ch = 0;
									}
									else
									{
										printf("\nEnter correct choice!");
									}
								}
								flag = 0;
								break;
							case 2:
								flag = 0;
								//Deactivate CFS function.......
							case 3:
								flag = 0;
								break;
								//Unregister function........
							case 4:
								break;
								flag = 0;
								//Make a call function.......
							case 5:
								uid = 0;
								flag = 0;
								break;
							case 6:
								exit(EXIT_SUCCESS);
							default:
								printf("\nInvalid Choice!Try Again");
						}
					}
				}
				break;
			case 3:
				exit("EXIT_SUCCESS");
			default:
				printf("\nInvalid Choice");
		}
	}
	return 0;
}

