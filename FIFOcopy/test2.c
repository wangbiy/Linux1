#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define ERR_EXIT(m) \
	do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)//使用do...while(0)在使用时起封装作用，否则在使用中间的代码时可能出现问题（比如在使用时有if else语句）
int main()
{
	int infd;
	infd=open("abc.bak",O_WRONLY|O_CREAT|O_TRUNC);//以只写方式打开,没有就创建
	if(infd<0)
		ERR_EXIT("open");
	int outfd;//命名管道的文件描述符
	outfd=open("tp",O_RDONLY);//以只读方式打开管道tp
	if(outfd<0)
		ERR_EXIT("open");
	char buf[1024];
	int s;
	while((s=read(outfd,buf,1024))>0)//将管道tp中的内容读到buf中
	{
		write(infd,buf,s);//将buf中的内容写到abc.bak中
	}
	close(infd);
	close(outfd);
	unlink("tp");
	return 0;
}
