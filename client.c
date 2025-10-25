#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("usage: ./a.out port_number ip_address\n");
		return 0;
	}

	int sfd,nsfd,len;
	struct sockaddr_in server_id;
	sfd=socket(AF_INET,SOCK_STREAM,0);

	if(sfd<0)
	{
		perror("socket");
		return 0;
	}
	perror("socket");
	server_id.sin_family=AF_INET;
	server_id.sin_port=htons(atoi(argv[1]));  
	server_id.sin_addr.s_addr=atoi(argv[2]);
	len=sizeof(server_id);
	if(connect(sfd,(struct sockaddr*)&server_id,len)<0)
	{
		perror("connect failure");
		return 0;
	}
	perror("connect");
	int num,check;
	srand(getpid());
	while(1)
	{
		num=rand()%100+1;
		printf("the random number we got is %d\n",num);
		write(sfd,&num,sizeof(num));
		read(sfd,&check,sizeof(check));
		if(check==1)
		{
		printf("Random number %d is prime number\n",num);
		break;
		}
		else 
		printf("Random number %d is Non prime number\n",num);
	}
	close(sfd);


}
