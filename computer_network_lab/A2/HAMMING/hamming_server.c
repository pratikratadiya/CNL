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
            int ackBuffer[10];
            int buffer[256];
              
        	int dataatrec[10],c,c1,c2,c3;
            
        	if (argc < 2) {
             fprintf(stderr,"ERROR, no port provided\n");
             exit(1);
         	}
    		
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

        
            
        bzero(buffer,256);
        read(connsd,buffer,255);
        
         printf("\nMessage from the client : \t");
         for(int j=0;j<7;j++)
         	printf("%d",buffer[j]);
        
        for(i=0;i<7;i++)
            dataatrec[i] = buffer[i];
     
        c1=dataatrec[6]^dataatrec[4]^dataatrec[2]^dataatrec[0];
        c2=dataatrec[5]^dataatrec[4]^dataatrec[1]^dataatrec[0];
        c3=dataatrec[3]^dataatrec[2]^dataatrec[1]^dataatrec[0];
        c=c3*4+c2*2+c1 ;
        	
        if(c==0) {
        		bzero(ackBuffer,10);
        		ackBuffer[0]=c;
                write(connsd,ackBuffer,sizeof(ackBuffer));
        }
        else {
        		bzero(ackBuffer,10);
        		ackBuffer[0]=c;
            write(connsd,ackBuffer,sizeof(ackBuffer));
            printf("\nError on position %d",c);
            
           
            printf("\nCorrect message is\n");
     
            //if errorneous bit is 0 we complement it else vice versa
            if(dataatrec[7-c]==0)
                dataatrec[7-c]=1;
            else
                dataatrec[7-c]=0;
            
            for (i=0;i<7;i++) 
                printf("%d",dataatrec[i]);
           
            }
         close(connsd);
         close(listensocket);

    }
