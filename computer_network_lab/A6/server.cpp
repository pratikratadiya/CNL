//A6 Server
#include <iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>  //for exit
#include<unistd.h>
#include<string.h>//for close
#include<stdio.h>
using namespace std;

int main()
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server,client;

	server.sin_family=AF_INET;
	server.sin_port=htons(8003);
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(sock,(struct sockaddr *)&server,sizeof(server)))
	{
		cout<<"Bind error"<<endl;
	}

	if(listen(sock,5)<0)
	{
		cout<<"EROOR on listen"<<endl;
	}

	socklen_t clilen=sizeof(client);
	int newsock=accept(sock,(struct sockaddr *)&client,&clilen);

	float a,b,ans1;
	char op[2];
	char n1[20],n2[20];

	while(1)
	{
		int n=recv(newsock,n1,20,0);
		cout<<"The first number is "<<n1<<endl;

		a=atof(n1);
		bzero((char *)n1,sizeof(n1));

		int o=recv(newsock,n2,20,0);
		cout<<"The second number is "<<n2<<endl;

		b=atof(n2);
		bzero((char *)n2,sizeof(n2));

		int p=recv(newsock,op,2,0);
		cout<<"The operator  is "<<op<<endl;

		switch(op[0])
		{			
			case '+':
			{
				char ans[20];
				ans1=a+b;
				cout<<"THe ans1 is "<<ans1<<endl;
				bzero((char *)ans,sizeof(ans));
				sprintf(ans,"%f",ans1);
				send(newsock,ans,strlen(ans),0);
				break;
			}
			case '-':
			{
				char ans[20];
				ans1=a-b;
				bzero((char *)ans,sizeof(ans));
				sprintf(ans,"%f",ans1);
				send(newsock,ans,strlen(ans),0);
				break;
			}
			case '*':
			{
				char ans[20];
				ans1=a*b;
				bzero((char *)ans,sizeof(ans));
				sprintf(ans,"%f",ans1);
				send(newsock,ans,strlen(ans),0);
				break;
			}
			case '/':
			{
				char ans[20];
				ans1=a/b;
				bzero((char *)ans,sizeof(ans));
				send(newsock,ans,strlen(ans),0);
				sprintf(ans,"%f",ans1);
			}
		}
		bzero((char *)op,sizeof(op));
	}
}
