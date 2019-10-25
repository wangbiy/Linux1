#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
//int main()
//{
//
//	//测试一下当父进程不读的时候，是什么情况
//	int fd[2]={0};
//	pipe(fd);
//	pid_t id=fork();
//	if(id==0)//child--->write
//	{
//		close(fd[0]);
//		const char* str="I am child";
//		int count=0;
//		while(1)
//		{
//			write(fd[1],str,strlen(str));
//			printf("%d\n",count+=strlen(str));
//
//	//		sleep(1);
//		}
//		exit(0);
//
//	}
//	else
//	{
//		close(fd[1]);
//		char buf[1024];
//		while(1)
//		{
//			ssize_t s=read(fd[0],buf,sizeof(buf)-1);
//			if(s>0)
//			{
//				buf[s]=0;
//				printf("%s\n",buf);
//			}
//			else if(s==0)
//			{
//				printf("read file end!\n");
//				break;
//			}
//			else
//			{
//				printf("read error!\n");
//				break;
//			}
//		}
//		waitpid(id,NULL,0);
//	}
//	return 0;
//}

int main()
{

	int fd[2]={0};
	pipe(fd);
	pid_t id=fork();
	if(id==0)//child--->write
	{
		close(fd[0]);
		const char* str="I am child";
		int count=0;
		while(1)
		{
			write(fd[1],str,strlen(str));
			printf("%d\n",count+=strlen(str));
			sleep(1);
		}
		exit(0);

	}
	else
	{
		close(fd[1]);
		char buf[1024];
		while(1)
		{
			sleep(5);//父进程5秒后读，这5秒中子进程一瞬间写完，子进程阻塞，父进程沉睡，5秒后打印数据
			ssize_t s=read(fd[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				printf("%s\n",buf);
			}
			else if(s==0)
			{
				printf("read file end!\n");
				break;
			}
			else
			{
				printf("read error!\n");
				break;
			}
			break;
		}
		close(fd[0]);//关掉读端文件描述符
		int status=0;
		waitpid(id,&status,0);//父进程拿到子进程的退出信息
		printf("signal:%d\n",status&0x7f);//拿到低7位表示的退出信号
	}
	return 0;
}
