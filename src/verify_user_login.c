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

int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(NAME_PW_DATABASE, "r");
	char *name_passwd;
	
	name_passwd = (char *)malloc(100 *sizeof(char));
	strcat(name_passwd, argv[1]);
	strcat(name_passwd, "    ");
	strcat(name_passwd, argv[2]);
	strcat(name_passwd, "\n");
	name_passwd[strlen(name_passwd)]='\0';
	
	char buf[100];
	
	
	while(feof(fp) == 0)
	{
		fgets(buf, 100, fp);
		if(strlen(buf)==0)
		{
			printf("Invalid username or password\n\n");
			exit(1);
		}
			
			
		buf[strlen(buf)]='\0';
		
		if(strcmp(buf,name_passwd) == 0)
		{
			printf("User verified\n\n");
			exit(0);
		}
	}
	printf("Invalid username or password\n\n");
	exit(1);
}
