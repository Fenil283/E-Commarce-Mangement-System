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

#define MAXLINE  8192  
#define LISTENQ  1024  

int open_listenfd(char *port) 
{
    struct addrinfo hints, *listp, *p;
    int listenfd, optval=1;
	char host[MAXLINE],service[MAXLINE];
    int flags;

    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;             
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; 
    hints.ai_flags |= AI_NUMERICSERV;            
    getaddrinfo(NULL, port, &hints, &listp);

    
    for (p = listp; p; p = p->ai_next) {
        
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
            continue;  

        
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,    
                   (const void *)&optval , sizeof(int));

		flags = NI_NUMERICHOST | NI_NUMERICSERV; 
		getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
        printf("host:%s, service:%s\n", host, service);

        
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
            break; 
        close(listenfd); 
    }

    
    freeaddrinfo(listp);
    if (!p) 
        return -1;

    
    if (listen(listenfd, LISTENQ) < 0) {
        close(listenfd);
	return -1;
    }
    return listenfd;
}

void echo(int connfd)
{
    char *message;
    write(connfd, "Hello", 6);
    while(1)
    {
    	    message = (char *)malloc(200*sizeof(char));
	    read(connfd, message, 200);
	    message[strlen(message)]='\0';
	    printf("\nCustomer: %s\n",message);
	    message[strlen(message)]='\0';
	    
	    if(strstr(message,"**"))
	    	break;
	    
	    printf("Enter your response: ");
	    fgets(message, 200, stdin);
	    message[strlen(message)]='\0';
	    write(connfd, message, strlen(message)+1);
	    free(message);
    }
}

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; 
    char client_hostname[MAXLINE], client_port[MAXLINE];
    listenfd = open_listenfd(argv[1]);
    while (1) {
	printf("Waiting for a new Client to connect\n");
        clientlen = sizeof(struct sockaddr_storage); /* Important! */
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        getnameinfo((struct sockaddr *) &clientaddr, clientlen,
        	client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
	printf("Start Communication with Client\n");
        echo(connfd);
	printf("End Communication with Client\n");
        close(connfd);
    }
    exit(0);
}

