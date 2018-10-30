#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>  //for exit
#include<unistd.h>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server,client;

	server.sin_family = AF_INET;
	server.sin_port   = htons(8003);
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(sock,(struct sockaddr*)&server,sizeof(server))){
		cout<<"\nBIND ERROR\n";
	}

	if (listen(sock,5)<0){
		cout<<"\nERROR ON LISTEN\n";
	}

	socklen_t clientlen = sizeof(client);
	int newsock = accept(sock,(struct sockaddr *)&client,&clientlen);

	float number1,number2,answer;
	char _operator[2],num1[20],num2[20];

	while(1){
		recv(newsock,num1,20,0);
		cout<<"\nThe first number is "<<num1<<endl;
		number1 = atof(num1);
		bzero((char*)num1,sizeof(num1));

		recv(newsock,num2,20,0);
		cout<<"\nThe second number is "<<num2<<endl;
		number2 = atof(num2);
		bzero((char*)num2,sizeof(num2));

		recv(newsock,_operator,2,0);
		cout<<"\nThe operator  is "<<_operator<<endl;

		switch(_operator[0]) {
			case '+':
			{
				char ans[20];
				answer = number1 + number2;
				bzero((char*)ans,sizeof(ans));
				sprintf(ans,"%f",answer);
				send(newsock,ans,strlen(ans),0);
				break;
			}
			case '-':
			{
				char ans[20];
				answer = number1 - number2;
				bzero((char*)ans,sizeof(ans));
				sprintf(ans,"%f",answer);
				send(newsock,ans,strlen(ans),0);
				break;
			}
			case '*':
			{
				char ans[20];
				answer = number1 * number2;
				bzero((char*)ans,sizeof(ans));
				sprintf(ans,"%f",answer);
				send(newsock,ans,strlen(ans),0);
				break;
			}
			case '/':
			{
				char ans[20];
				answer = number1 / number2;
				bzero((char*)ans,sizeof(ans));
				sprintf(ans,"%f",answer);
				send(newsock,ans,strlen(ans),0);
				break;
			}
		}
		bzero((char*)_operator,sizeof(_operator));
	}
}