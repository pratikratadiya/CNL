
# include<stdlib.h>
# include<netinet/in.h>//The header file in.h contains constants and structures needed for internet domain addresses
# include<time.h>
# include<arpa/inet.h>
# include<string.h>
# include<unistd.h> //read write close functions
# include<netdb.h>
# include<stdio.h>//This header file contains declarations used in most input and output and is typically included in all C programs.
#include<sys/types.h> 
#include<sys/socket.h> 

int  main(int argc, char *argv[])
{ 
	struct sockaddr_in serversocket;
  	int listensocket,i,connsd,size;

	int data[10],ackData[10];
    int dataatrec[10],c,c1,c2,c3;
    	
	if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
        printf("\tThis is Chat Client.\n");
        bzero((char *)&serversocket,sizeof(serversocket));

        listensocket=socket(AF_INET,SOCK_STREAM,0);//int socket(domain, type, protocol)

        if(listensocket<0)
                printf("Socket Could Not Be Created");
        else
                printf("Socket Created Succesfully");

        printf("\nListensocket Value : %d",listensocket);

        serversocket.sin_family=AF_INET;
        serversocket.sin_port=htons(atoi(argv[2]));
        serversocket.sin_addr.s_addr=INADDR_ANY;
      	i = connect(listensocket,(struct sockaddr *)&serversocket,sizeof(serversocket)); /*The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr. The addrlen argument specifies the size of addr.*/

        if(i==0)
                printf("\nConnect SUCCESS\n");
        else
                printf("\nConnect ERROR\n");
	
	
	 bzero(data,10);
	 printf("Enter 4 bits of data one by one\n");
   	 scanf("%d",&data[0]);
   	 scanf("%d",&data[1]);
   	 scanf("%d",&data[2]);
   	 scanf("%d",&data[4]);
    
     //Calculation of even parity
    data[6]=data[0]^data[2]^data[4];
    data[5]=data[0]^data[1]^data[4];
    data[3]=data[0]^data[1]^data[2];
 
 
	 printf("\nEncoded data is\n");
    
    for(i=0;i<7;i++)
        printf("%d",data[i]);
        
        
		write(listensocket,data,sizeof(data));
		
		read(listensocket,ackData,10);
		printf("\nackData :%d",ackData[0]);
		
		if(ackData[0]==0)
		{
			printf("SUCCESSFUL! No Error!");
		}	
		else
		{
			printf("Error!");		
		}
	
 	close(listensocket);
}



