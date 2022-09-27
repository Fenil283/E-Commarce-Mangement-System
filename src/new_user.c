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

#define NAME_PW_DATABASE "/home/ubantu20/database/name_pw_data.txt"


char *details[]={"Enter your name: ", "Enter your DOB: ", "Enter email ID: ", "Enter Mobile number: ", "Enter Address Line 1: ", 
			 "Enter Address Line 2: ", "Enter City: ", "Enter Country: "};
			 
char *field[] = {"Name: ", "Date of Birth: ", "Email ID: ", "Mobile Number: ", "Address Line 1: ", "Address Line 2: ", "City: ", 
			 "Country: "};
			 
char *oh_file_line1 = "Date & Time             	Product Name            Type           Price     Qty.       Amt.\n";
			 
int number_of_fields=8; 
FILE *fd,*fp,*npdb;
char *fn,*name,*temp;
char oh_file[1024],new_entry[1024];



int make_usr_dir()
{
	strcat(fn,name);
	strcat(fn,"/");
	fn[strlen(fn)]='\0';
	return mkdir(fn,0777);
}

int make_usr_profile()
{
	char *ud_file, *usr_ip;
	ud_file = (char *)malloc(150*sizeof(char));
	strcat(ud_file, fn);
	strcat(ud_file, "user_profile.txt");
	ud_file[strlen(ud_file)]='\0';
	fd = fopen(ud_file, "w");
	
	//writing in file
	temp = (char *)malloc(150*sizeof(char));
	strcat(temp, field[0]);
	strcat(temp, name);
	temp[strlen(temp)]='\n';
	
	fputs(temp, fd);  //writing name
	int curr_fld=1;  //current field
	
	while(curr_fld < number_of_fields)
	{
		temp = (char *)malloc(150*sizeof(char));
		usr_ip = (char *)malloc(100*sizeof(char));
		strcat(temp, field[curr_fld]);
		
		printf("%s",details[curr_fld]);
		if (curr_fld==1)
			getchar();
		fgets(usr_ip, 100, stdin);
		usr_ip[strlen(usr_ip)]='\0';
		
		strcat(temp, usr_ip);
		temp[strlen(temp)]='\0';
		fputs(temp, fd);
		
		curr_fld++;	
	}
	return 0;
}

int insert_created_field()
{
	time_t t;
	time(&t);
	
	temp = (char *)malloc(150*sizeof(char));
	strcat(temp, "Created: ");
	strcat(temp, ctime(&t));
	temp[strlen(temp)]='\0';
	
	fputs(temp, fd);
	return 0;
}

int make_order_history_txt()
{
	strcat(oh_file, fn);
	strcat(oh_file, "history.txt");
	oh_file[strlen(oh_file)]='\0';
	
	fp = fopen(oh_file,"w");
	fputs(oh_file_line1, fp);
	return 0;
}

int take_passwd()
{
	char passwd[50],con_passwd[50];
	while(1)
	{
		printf("Enter your password (without spaces): ");
		scanf("%s", passwd);
		passwd[strlen(passwd)]='\0';  
		  
		//confirm field
		printf("Confirm password: ");
		scanf("%s", con_passwd);
		con_passwd[strlen(con_passwd)]='\0';   
		
		if(strcmp(passwd,con_passwd))
		{
			printf("Confirmed Password Invalid. Please try again.\n");
		}
		else
			break;
	}
	
	//printf("%s\n",name);
	strcat(new_entry, name);
	strcat(new_entry, "    ");
	strcat(new_entry, passwd);
	strcat(new_entry, "\n");
	new_entry[strlen(new_entry)]='\0';
	//printf("%s\n",new_entry);
	
	npdb = fopen(NAME_PW_DATABASE, "a");
	fputs(new_entry, npdb);
	fclose(npdb);
	return 0;
}

int main()
{	
	name = (char *)malloc(100*sizeof(char));
	fn = (char *)malloc(100*sizeof(char));
	int childPid, status;
	
	
	strcat(fn,"/home/ubantu20/database/");
	printf("%s", details[0]);
	scanf("%s", name);
	name[strlen(name)]='\0';
	
	if(fork()==0)
	{
		execl("./check_already_if_user.out", "./check_already_if_user.out", name, NULL);
		printf("Error in exec check\n");
	}
	else
	{
		childPid = wait(&status);
		
		if(WEXITSTATUS(status)==1)
		{
			printf("This username is already registered. Please try another username.\n\n");
			exit(1);
		}
		
		
		//making of user directory
		make_usr_dir();
		
		
		//making of user profile txt file
		make_usr_profile();
		
		//created field
		
		insert_created_field();
		
		//making order history file
		make_order_history_txt();
		
		//taking passwd
		take_passwd();
		
		//closing files
		fclose(fd);
		fclose(fp);
		
		exit(0);
	}
}





