	/*
	 * echo_server.c
	 * Written by SW. Yoon
	 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define BUFSIZE 1024

void error_handling(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	int str_len;
	char message[BUFSIZE];

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;

	if(argc!=2)
	{
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0); //서버 소켓 생성
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)//소켓에 주소 할당
		error_handling("bind() error");

	if(listen(serv_sock, 5)==-1) //연결 요청 대기 상태로 진입
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);
	while(1)
	{
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); //연결 요청 수락
		if(clnt_sock==-1)
			error_handling("accept() error");
	
		//데이터 수신 및 전송
		while((str_len=read(clnt_sock,message,BUFSIZE))!=0)
		{
			write(clnt_sock, message, str_len);
			write(1,message,str_len);
		}
	
		close(clnt_sock); //연결 종료
	}
	return 0;
}


void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

