#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	const char* msg1="hello printf\n";
	const char* msg2="hello fwrite\n";
	const char* msg3="hello write\n";

	printf("%s",msg1);
	fwrite(msg2,1,strlen(msg2),stdout);
	write(1,msg3,strlen(msg3));
	fork();
	return 0;

}
//{
//	int fd=open("log0.txt",O_WRONLY);
//	if(fd<0)
//	{
//		printf("open error\n");
//	}
//	dup2(fd,1);
//	printf("hello world:%d\n",fd);
//	fflush(stdout);
//	close(fd);
//	return 0;
//}

//	char c[1024];
//	ssize_t s=read(fd,c,1024); 
//	if(s>0)
//	{
//		c[s]=0;//因为read不是C中的函数，不能保证将\0读到c中
//		printf("s:%d\n",s);
//		printf("%s\n",c);
//	}
//	close(fd);
//	return 0;
//}
//int main()
//{
//	close(1);
//	int fd0=open("log0.txt",O_WRONLY|O_APPEND);
//	const char* msg="hello bit!\n";
//	printf("hello world!\n");
//	fflush(stdout);
//	close(fd0);
//	return 0;
//}
//int main()
//{
//	close(1);
//
//	int fd0=open("log0.txt",O_WRONLY|O_CREAT,0644);
//	int fd1=open("log1.txt",O_WRONLY|O_CREAT,0644);
//	int fd2=open("log2.txt",O_WRONLY|O_CREAT,0644);
//	int fd3=open("log3.txt",O_WRONLY|O_CREAT,0644);
//	int fd4=open("log4.txt",O_WRONLY|O_CREAT,0644);
//	int fd5=open("log5.txt",O_WRONLY|O_CREAT,0644);
//	printf("fd0:%d\n",fd0);
//	printf("fd1:%d\n",fd1);
//
//	printf("fd2:%d\n",fd2);
//	printf("fd3:%d\n",fd3);
//	printf("fd4:%d\n",fd4);
//	printf("fd5:%d\n",fd5);
//
//	fflush(stdout);
//	close(fd0);
//	close(fd1);
//	close(fd2);
//	close(fd3);
//	close(fd4);
//	close(fd5);

//const char* msg="hello world!\n";
//fprintf(stdout,"%s",msg);
////fputs(msg,stdout);
//return 0;
//}
/*{
	FILE* fp=fopen("log.txt","w");
	if(!fp)
	{
		perror("fopen");
	}
	const char* msg="hello world!\n";
	int i=0;
	for(;i<10;++i)
	{
		fwrite(msg,strlen(msg),1,fp);
	}
	fclose(fp);
	return 0;
}*/
