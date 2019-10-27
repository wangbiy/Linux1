#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#define ERR_EXIT(m) \
	do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)//使用do...while(0)在使用时起封装作用，否则在使用中间的代码时可能出现问题（比如在使用时有if else语句）
int main()
{
	mkfifo("tp",0644);
	int infd;
	infd=open("abc",O_RDONLY);//以只读方式打开
	if(infd<0)
		ERR_EXIT("open");
	int outfd;//命名管道的文件描述符
	outfd=open("tp",O_WRONLY);
	if(outfd<0)
		ERR_EXIT("open");
	char buf[1024];
	int s;
	while((s=read(infd,buf,1024))>0)//将文件abc中的内容读到buf中
	{
		write(outfd,buf,s);//将buf中的内容写到管道tp中
	}
	close(infd);
	close(outfd);
	return 0;
}
