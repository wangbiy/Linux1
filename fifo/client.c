#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	int fd=open("fifo",O_WRONLY);//客户端以只写打开
	if(fd<0)
	{
		printf("open errno");
		return 1;
	}
	char buf[1024];
	while(1)
	{
		printf("Please enter your message:");
		fflush(stdout);
		ssize_t s=read(0,buf,sizeof(buf)-1);//从标准输入读
		if(s>0)
		{
			buf[s-1]=0;//因为敲了回车之后，会空出来一行，服务端接收到这个空出来的行，因此将buf[s-1]=0
			write(fd,buf,strlen(buf));//将buf中的内容写到管道中
		}
		else if(s==0)
		{
			printf("client exit!\n");
			break;
		}
		else
		{
			printf("read error\n");
			break;
		}
	}
	close(fd);
	return 0;
}
