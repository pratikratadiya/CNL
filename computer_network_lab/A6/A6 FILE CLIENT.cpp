
#include <iostream>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;
#define SERVER_ADDRESS "127.0.0.1"
#define PORT 8777
void die(char *error)
{
	perror(error);
	exit(1);
}
int main() {

	    struct sockaddr_in server_addr;
		int sock=socket(AF_INET,SOCK_STREAM,0);
		if(sock<0)
		                cout<<"Socket Could Not Be Created";
		        else
		                cout<<"Socket Created Succesfully";
		server_addr.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);
		server_addr.sin_family=AF_INET;
		server_addr.sin_port=htons(PORT);

		int status=connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
		 if(status==0)
			cout<<"\nCONNECT SUCCESS!.";
		 else
			 die("connect");
long long int msg_len;
		 char buffer[256];

	{
			 cout<<"Wating for server to send  filename.";
				char filename[100];
				bzero((char *)filename,sizeof(filename));
				msg_len=recv(sock,filename,100,0);
				if(msg_len==-1)
					die("Filename error");
				cout<<"\nFilename:"<<filename;


				char *filebuff=new char[90000*80];


				bzero((char *)filebuff,sizeof(filebuff));
				msg_len=recv(sock,filebuff,90000*80,0);
				ofstream fout;
				fout.open(filename,ios::out|ios::binary);
				if(!fout)
					die("CANNOT CREATE FILE");
				else
				{
					fout.write(filebuff,msg_len);
					fout.close();
					cout<<"File received";
				}
			}
	return 0;
}
