#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include<stdlib.h>
int prime_check(int num)
{
	int i;
		for(i=2;i<num;i++)
		{
			if(num%i==0)
				break;
		}
		if(num==i)
		{
			return 1;
			//break;
        	}
		else
			return 0;
}
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
	if(bind(sfd,(struct sockaddr*)&server_id,len)<0)
	{
		perror("bind failure");
		return 0;
	}
	perror("bind");
	if(listen(sfd,5)<0)
	{
		perror("listen failure");
		return 0;
	}
	perror("listen");
	printf("waiting for client to connect\n");

	nsfd=accept(sfd,(struct sockaddr*)&server_id,&len);
	if(nsfd<0)
	{
		perror("accept failure");
		return 0;
	}
	perror("accept");
	printf("connection successful\n");
	int num,i,j;
	while(1)
	{
		read(nsfd,&num,sizeof(num));
		j=prime_check(num);
		write(nsfd,&j,sizeof(j));
	}
	close(sfd);
	close(nsfd);


}
