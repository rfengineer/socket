/*
NAME:           bind.c
DESCRIPTION:    self test of skill on socket programming.             
SYNOPISIS:      bind
HISTORY:        Version 14.0
COPYRIGHT:      GNU General Public License
AUTHORS:        Ray Dall
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int Fail(int state, char *response)
        {
        if(state<0)
                {
                printf("%s Failure\n\n",response);
                exit(EXIT_FAILURE);
                }
        else
                {
                printf("%s Success\n\n",response);
                }
        }

int main(int argc, char *argv[])
{
system("clear");

//VARIABLES
        int sock_inet;
        struct sockaddr_in sock_adr;
        socklen_t socklen;

//create the socket
        if(sock_inet=socket(PF_INET,SOCK_STREAM,0))Fail(1,"Socket Creation ");


//setup the address
        if(memset(&sock_adr,0,sizeof(sock_adr)))Fail(1,"memset()");;
        if(sock_adr.sin_family=AF_INET)Fail(1,"socket family");
        if(sock_adr.sin_port=htons(9000))Fail(1,"socket port");
        if(inet_aton("192.168.2.66",&sock_adr.sin_addr))Fail(1,"IP Address");

if(sock_adr.sin_port=htons(9000))Fail(1,"socket port");
        if(inet_aton("192.168.2.66",&sock_adr.sin_addr))Fail(1,"IP Address");

//bind the socket
        socklen=sizeof(sock_adr);
        if(bind(sock_inet,(struct sockaddr *)&sock_adr,socklen))Fail(1,"socket bind");


//listen
        listen(sock_inet,250);

//close
        close(sock_inet);
printf("\nPROCESS COMPLETE\n\n");
return(0);
}

/*
Followup:
Still need to work on concepts like read(), write(), etc as it pertains to the use of internet sockets.
*/
