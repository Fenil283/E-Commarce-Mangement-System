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

int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	char buf[100];
	char ch;

	int c;
	while ((c = fgetc(fp)) != EOF)
		fputc(c, stdout);
	
	exit(0);
}
