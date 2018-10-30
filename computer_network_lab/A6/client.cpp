//A6 Client
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>  //for exit
#include<unistd.h>
#include<arpa/inet.h>//for close
using namespace std;

int main(int argc,char **argv) {

	int sock=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server;

	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	cout<<ntohl(server.sin_addr.s_addr );

	connect(sock,(struct sockaddr *)&server,sizeof(server));

	int n;
	char a[20];
	char b[20];
	char c[20];
	char ans[20];

	while(1)
	{
		cout<<"Enter first number"<<endl;
		cin>>a;
		send(sock,a,strlen(a),0);
		bzero((char*)a,sizeof(a));

		cout<<"Enter second number"<<endl;
		cin>>b;
		send(sock,b,strlen(b),0);
		bzero((char*)b,sizeof(b));

		cout<<"Enter operator "<<endl;
		cin>>c;
		send(sock,c,20,0);
		bzero((char*)c,sizeof(c));

		recv(sock,ans,20,0);
		cout<<"RESULt OF operation "<<ans<<endl;
		bzero((char*)ans,sizeof(ans));
	}
}