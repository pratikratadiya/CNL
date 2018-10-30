#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>  //for exit
#include<unistd.h>
#include<arpa/inet.h>//for close
using namespace std;

int main(int argc, char const *argv[])
{
	int n;
	char a[20],b[20],c[20],ans[20];

	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port   = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	cout<<ntohl(server.sin_addr.s_addr);

	connect(sock,(struct sockaddr *)&server,sizeof(server));

	while(1){

		cout<<"\nEnter First Number\n";
		cin>>a;
		send(sock,a,strlen(a),0);
		bzero((char*)a,sizeof(a));

		cout<<"\nEnter Second Number\n";
		cin>>b;
		send(sock,b,strlen(b),0);
		bzero((char*)b,sizeof(b));

		cout<<"\nEnter Operator\n";
		cin>>c;
		send(sock,c,strlen(c),0);
		bzero((char*)c,sizeof(c));

		recv(sock,ans,20,0);
		cout<<"Result:"<<(float)atof(ans);
		bzero((char*)ans,sizeof(ans));		
	}
}