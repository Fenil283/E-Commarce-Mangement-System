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

char* my_substr(char *sp, char *mid)
{
	char *p = (char *)malloc(60 *sizeof(char));
	int i=0;
	while(sp!=mid)
	{
		p[i]=*sp;
		sp++;
		i++;
	}
	p[i]='\0';
	return p;
}

int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(NAME_PW_DATABASE, "r");
	char *name, *mid;
	name = (char *)malloc(100 *sizeof(char));
	strcat(name, argv[1]);
	
	for(int i=2;i<argc;i++)
	{
		strcat(name," ");
		strcat(name,argv[i]);
	}
	name[strlen(name)]='\0';
	
	char buf[100];

	while(feof(fp) == 0)
	{
		fgets(buf, 100, fp);
		if(strlen(buf)==0)
			exit(0);
			
		buf[strlen(buf)]='\0';
		
		mid = strstr(buf, "    ");
		
		if(strcmp(my_substr(buf,mid),name) == 0)
		{
			exit(1);
		}
	}
	exit(0);
}
