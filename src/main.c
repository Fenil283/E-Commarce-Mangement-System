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

char *choices[] = {"1. New user (Sign up)", "2. Log in", "3. About us", "4. Customer Care", "5. Exit"};

void display_interface()
{
	for(int i=0;i<5;i++)
	{
		printf("%s\n",choices[i]);
	}
}

int main(int argc, char *argv[])
{
	int choice_no,flag_usr=1,childPid,status;
	//Sajavat baki
	
	printf("\n\t\t  ---Welcome to IT215--- \n\n");
	

	while(flag_usr)
	{
		display_interface();
		
		printf("Enter your choice: ");
		scanf("%d", &choice_no);
		
		switch(choice_no)
		{
			case 1:
			{
				if(fork()==0)
				{
					execl("./new_user.out", "./new_user.out", NULL);
					printf("Error in exec new_user\n");
				}
				childPid = wait(&status);
				
				if(WEXITSTATUS(status) == 0)
					printf("\nAccount created, You can Log in now\n\n");
				break;
			}
			case 2:
			{
				if(fork()==0)
				{
					execl("./login_user.out", "./login_user.out", NULL);
					printf("Error in exec login_user\n");
				}
				childPid = wait(&status);
					if(WEXITSTATUS(status)==1)
						continue;
				printf("\n\n");
				break;
			}
			case 3: //About us
			{
				printf("\n\t\t  ---About us--- \n\n");
				printf("Our website is made on the learing basis\n"); 
				printf("Which will include software programming \n");
				printf("File I/O\n");
				printf("Process Manangment\n");
				printf("Signal Handling\n");
				printf("Client server\n\n");
				printf("\n\n");
				break;
			}
			case 4: 
			{
				int len_port= (int)((ceil(log10(15000))+1)*sizeof(char));
				char sport[len_port];
				
				sprintf(sport, "%d", 15000);
				
				
				if(fork()==0)
				{
					execl("./customer_client.out", "./customer_client.out", "localhost", sport, NULL);
					printf("Error in exec client\n");
				}
				
				childPid = wait(&status);
				break;
			}
			case 5:
			{
				printf("Thanks for visiting us.\n\n");
				flag_usr=0;
				break;
			}
			default:
			{
				printf("Invalid choice. Please try again.\n");
			}
		}
	}
}
