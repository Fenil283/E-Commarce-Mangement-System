#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <math.h>

#define	MAXLINE	 1024  

int open_clientfd(char *hostname, char *port) {
    int clientfd;
    struct addrinfo hints, *listp, *p;
	char host[MAXLINE],service[MAXLINE];
    int flags;

    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;  
    hints.ai_flags = AI_NUMERICSERV;  
    hints.ai_flags |= AI_ADDRCONFIG;  
    getaddrinfo(hostname, port, &hints, &listp);
  
    
    for (p = listp; p; p = p->ai_next) {
        
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue; 

		flags = NI_NUMERICHOST | NI_NUMERICSERV; 		
		getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
        printf("host:%s, service:%s\n", host, service);
		
        
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) 
		{
			printf("Connected to server %s at port %s\n", host, service);
            break; 
		}
        close(clientfd); 
    } 

    
    freeaddrinfo(listp);
    if (!p) 
        return -1;
    else    
        return clientfd;
}


int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, *buf;
    host = argv[1];
    port = argv[2];
    clientfd = open_clientfd(host, port);
    buf = (char *)malloc(200*sizeof(char));
    int i=0;
    printf("\nNote: Type ** to exit chat\n\n");
    while (1) 
    {
    	buf = (char *)malloc(200*sizeof(char));
    	read(clientfd, buf, 200);
    	buf[strlen(buf)]='\0';
    	
    	printf("\nServer: %s\n", buf);
    	if (i==0)
    	{
    		printf("\n");
    		i++;
    	}
    	
    	printf("Enter your reply: ");
    	fgets(buf, 200, stdin);
    	buf[strlen(buf)]='\0';
    	
    	if (strstr(buf,"**"))
    	{
    		write(clientfd, "**", 3);
    		printf("Always here to help you.\n\n");
    		break;
    	}
    	write(clientfd, buf, strlen(buf)+1);
    	free(buf);
    }
    close(clientfd);
    exit(0);
}
