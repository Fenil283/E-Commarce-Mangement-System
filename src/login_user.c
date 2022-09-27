#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <termios.h>

#define NAME_PW_DATABASE "/home/ubantu20/database/name_pw_data.txt"

char *ud_file,*oh_file,*fn,*name,*passwd;

char *usr_choices[] = {"1. Display User Profile", "2. Display Order History", "3. Place an order", "4. Logout"};

void display_choices()
{
	for(int i=0;i<4;i++)
		printf("%s\n",usr_choices[i]);
}

int getch(void)
{
    struct termios oldpara, newpara;
    int cc;
    tcgetattr(STDIN_FILENO, &oldpara);
    newpara = oldpara;
    newpara.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newpara);
    cc = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldpara);
    return cc;
}

void take_usrname_passwd()
{
	name = (char *)malloc(100*sizeof(char));
	passwd = (char *)malloc(100*sizeof(char));
	
	printf("press back for previous page.\n\n");
	
	printf("Enter your Username: ");
	scanf("%s", name);
	name[strlen(name)]='\0';
	
	if(strcmp(name,"back") == 0)
		exit(1);
	
	
	printf("Enter your password: ");
	alarm(10);
	
	int i=0;
	getchar();
	char c;
	passwd[i] = 'f';
	while(1)
    	{
    		passwd[i] = getch();		
    		
    		if(passwd[i]=='\n')
    		{
    			passwd[i]='\0';
    			alarm(0);
    			break;
    		}
    		i++;
    		write(2,"*",1);
    	}
    	
	passwd[strlen(passwd)]='\0';
	printf("\n");
}

void form_paths()
{
	fn = (char *)malloc(100*sizeof(char));
	ud_file = (char *)malloc(100*sizeof(char));
	oh_file = (char *)malloc(100*sizeof(char));
	
	strcat(fn,"/home/ubantu20/database/");
	strcat(fn,name);
	strcat(fn,"/");
	fn[strlen(fn)]='\0';
	
	strcat(ud_file, fn);
	strcat(ud_file, "user_profile.txt");
	ud_file[strlen(ud_file)]='\0';
	
	strcat(oh_file, fn);
	strcat(oh_file, "history.txt");
	oh_file[strlen(oh_file)]='\0';
}


int main()
{
	int childPid, status, flag=0, choice_no, flag_usr=1;
	
	
	
	while(flag_usr)
	{
		if(flag==0)
		{
			take_usrname_passwd();
			
			if(fork()==0)
			{
				execl("./verify_user_login.out","./verify_user_login.out", name, passwd, NULL);
				printf("Error in exec verify_user_login\n");
			}
			
			childPid = wait(&status);
			if(WEXITSTATUS(status)==1)
				continue;
			

			
			form_paths();	
			flag=1;
		}
		
		
		display_choices();
		
		printf("Enter your choice: ");
		scanf("%d",&choice_no);
		
		switch(choice_no)
		{
			case 1:
			{
				printf("\n\t\t ---User Profile---\n");
				if(fork()==0)
				{
					execl("./open_usr_profile.out", "./open_usr_profile.out", ud_file, NULL);
					printf("Error in exec open_usr_profile\n");
				}
				childPid = wait(&status);
				printf("\n\n");
				break;
			}
			case 2: //open history
			{
				printf("\n\t\t ---User Order History---\n");
				if(fork()==0)
				{
					execl("./open_usr_history.out", "./open_usr_history.out", oh_file, NULL);
					printf("Error in exec open_usr_history\n");
				}
				childPid = wait(&status);
				printf("\n\n");
				break;
			}
			case 3: //place order
			{
				if(fork()==0)
				{
					execl("./place_order.out", "./place_order.out", oh_file, NULL);
					printf("Error in exec place_order\n");
				}
				childPid = wait(&status);
				printf("\n\n");
				break;
			}
			case 4:
			{
				flag_usr=0;
				break;
			}
			default:
			{
				printf("Invalid choice. Please try again.\n\n");
			}
		}
	}
}
