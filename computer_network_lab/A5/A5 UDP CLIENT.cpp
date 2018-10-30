//============================================================================
// Name        : A5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

#define PORT 8999
#define buflen 1000;
#define SERVER_ADDRESS "127.0.0.1"
void die(char *s) //method to print error and exit
{
	perror(s);
	exit(1);
}
int main() {

	struct sockaddr_in server_addr;
	cout<<"\nUDP Client\nNote:-For receiving data, First Select Receive Option And then Select Send Option";

	//step 1: Creating Socket
	int sock;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1) //SOCK_DGRAM= SOCKET Type is datagram
	{											//0=PACKET TYPE USUALLY 0 or (IPPROTo_UDP)
		die("SOCKET CREATE ERROR");
	}
	//specify server address type, port as 8999 and address
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);; //INADDR_ANY takes current IP Address of PC
	//htons() converts the unsigned short integer hostshort from host byte order to network byte order.

	socklen_t cli=sizeof(server_addr);
	int slen=sizeof(server_addr);
	int choice,msg_len;
	char buffer[1000];
	cout<<"\nEnter msg to server:";
	cin.getline(buffer,sizeof(buffer));
	msg_len=sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)& server_addr,slen);
	do
	{
		cout<<"\nMENu\n1. CHAT \n2.REceive FILE\n3.Send File\n0.EXIT\nENter your choice:";
		cin>>choice;
		switch(choice)
		{
		case 1:
		{
			while(1)
			{
				bzero((char *)buffer,sizeof(buffer));
				cout<<"\nEnter msg to server:";
				cin.getline(buffer,sizeof(buffer));
				msg_len=sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)& server_addr,slen);
				bzero((char *)buffer,sizeof(buffer));

				if(msg_len<0)
					die("sending eerror");

				msg_len=recvfrom(sock,buffer,1000,0,(struct sockaddr *) &server_addr,&cli);
				if(msg_len>0)
					cout<<"SERVER:"<<buffer;

				if(strcmp(buffer,"bye")==0)
					break;

				bzero((char *)buffer,sizeof(buffer));
			}
			break;
		}
		case 2:
		{
			char filename[100];
			bzero((char *)filename,sizeof(filename));
			msg_len=recvfrom(sock,filename,99,0,(struct sockaddr*)&server_addr,&cli);
			if(msg_len==-1)
				die("Filename error");
			cout<<"\nFilename:"<<filename;

			int filesize;
			msg_len=recvfrom(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr*)&server_addr,&cli);
			cout<<"\nFileSize:"<<filesize;
			char *filebuff=new char[filesize];


			bzero((char *)filebuff,sizeof(filebuff));
			msg_len=recvfrom(sock,filebuff,filesize,0,(struct sockaddr*)&server_addr,&cli);
			ofstream fout;
			fout.open(filename,ios::out|ios::binary);
			if(!fout)
				die("CANNOT CREATE FILE");
			else
			{
				fout.write(filebuff,filesize);
				fout.close();
				cout<<"File received";
			}
		}
			break;

		case 3:
		{	cout<<"\nENter Filename:";
						char filename[100];
						cin>>filename;
						fstream fout1;
						fout1.open(filename,ios::in|ios::out|ios::binary);
						fout1.seekg(0,ios::end);
						int filesize=fout1.tellg(); //get file size
						char *filebuff=new char[filesize];
						fout1.seekg(0,ios::beg);
						fout1.read(filebuff,filesize); //reading file content

						msg_len=sendto(sock,filename,strlen(filename),0,(struct sockaddr *)&server_addr,slen); //send filename
									if(msg_len==-1)
										die("Filename error");

						msg_len=sendto(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&server_addr,slen); //send filesize
						if(msg_len==-1)
							die("Filesize error");



						msg_len=sendto(sock,filebuff,filesize,0,(struct sockaddr *)&server_addr,slen); //send file conetents
						if(msg_len==-1)
							die("File transmission error");
						else
							cout<<"Transmission Successful";
						fout1.close();
		}
						break;
		}
	}while(choice!=0);

	close(sock);
	return 0;
}



