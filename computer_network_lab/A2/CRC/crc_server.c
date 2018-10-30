# include<stdlib.h>
# include<netinet/in.h>//The header file in.h contains constants and structures needed for internet domain addresses
# include<time.h>
# include<arpa/inet.h>
# include<string.h>
# include<unistd.h>
# include<netdb.h>
#include<stdio.h> //This header file contains declarations used in most input and output and is typically included in all C programs.
#include<sys/types.h> //This header file contains definitions of a number of data types used in system calls. These types are used in the next two include files.
#include<sys/socket.h> //The header file socket.h includes a number of definitions of structures needed for sockets.
int main(int argc,char *argv[])
{
        int listensocket, i, connsd, size;
        struct sockaddr_in serversocket,clientsocket;
        char  recvbuff[100];
        int j,keylen,msglen;
	char input[100] = {"100000001"}, key[30],temp[30],quot[100],rem[30],key1[30];
	char input1[100];
         //char buffer[256];
        
	if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     	}
        printf("\t This is Chat Server.\n");
		
        listensocket=socket(AF_INET,SOCK_STREAM,0);//int socket(domain, type, protocol)

        if(listensocket<0)
                printf("Socket Could Not Be Created");
        else
                printf("Socket Created Succesfully");

        printf("\nListensocket Value : %d",listensocket);
        
        bzero((char *)&serversocket,sizeof(serversocket));

        serversocket.sin_family=AF_INET;
        serversocket.sin_port=htons(atoi(argv[1]));
        serversocket.sin_addr.s_addr=INADDR_ANY;
        i = bind(listensocket,(struct sockaddr *) &serversocket,sizeof(serversocket));/*The bind() system call binds a socket to an address, in this case the address of the current host and port number on which the server will run. It takes three arguments, the socket file descriptor, the address to which is bound, and the size of the address to which it is bound. The second argument is a pointer to a structure of type sockaddr, but what is passed in is a structure of type sockaddr_in, and so this must be cast to the correct type. This can fail for a number of reasons, the most obvious being that this socket is already in use on this machine. */
        if(i == 0)
                printf("\nBinding Is Succesful\n");
        else
                printf("\n Binding Not Succesful\n");

        i = listen(listensocket,1);/*the listen system call allows the process to listen on the socket for connections. The first argument is the socket file descriptor, and the second is the size of the backlog queue, i.e., the number of connections that can be waiting while the process is handling a particular connection. This should be set to 5, the maximum size permitted by most systems*/
        if(i == 0)
               printf("Listen SUCCESS\n");
        else
                printf("Listen ERROR\n");

        size = sizeof(struct sockaddr_in);

        connsd = accept(listensocket, (struct sockaddr *) &clientsocket,&size);/*The accept() system call causes the process to block until a client connects to the server. Thus, it wakes up the process when a connection from a client has been successfully established. It returns a new file descriptor, and all communication on this connection should be done using the new file descriptor. The second argument is a reference pointer to the address of the client on the other end of the connection, and the third argument is the size of this structure. */

	
	bzero(recvbuff,100);
	read(connsd,recvbuff,100);

	printf("\nMessage from the client : %s\t",input);
	
	strcpy(input1,recvbuff);
	
	printf("\nEnter Key: ");
	gets(key);
	
	keylen=strlen(key);
	msglen=strlen(input);
	
	strcpy(key1,key);


	for (i=0;i<keylen;i++)
		temp[i]=input[i];

	for (i=0;i<msglen-keylen+1;i++)
	{
		quot[i]=temp[0];
		if(quot[i]=='0')
         		for (j=0;j<keylen;j++)
         			key[j]='0'; 
         	else
			for (j=0;j<keylen;j++)
				key[j]=key1[j];

		for (j=keylen-1;j>0;j--)
		{
			if(temp[j]==key[j])
				rem[j-1]='0';
			else
				rem[j-1]='1';
		}
		printf("\nRemainder : %s\t",rem);

	rem[keylen-1]=input[i+keylen];
	strcpy(temp,rem);
	}
	
	strcpy(rem,temp);
	printf("\nQuotient is ");
	for (i=0;i<msglen;i++)
	printf("%c",quot[i]);
     
	printf("\nRemainder is ");
	for (i=0;i<keylen-1;i++)
	printf("%c",rem[i]);

        close(connsd);
     close(listensocket);
}

