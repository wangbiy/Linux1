#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
	pid_t id=fork();
	if(id==0)
	{
		printf("child:pid:%d,ppid:%d\n",getpid(),getppid());
		sleep(10);
		exit(13);
		//child
	}
	else
	{
		printf("father:pid:%d,ppid:%d\n",getpid(),getppid());
		int status;
		sleep(25);
		while(1)
		{
			int ret=waitpid(id,&status,WNOHANG);
			if(ret<0)
			{
				printf("wait error,wait ret:%d\n",ret);
				break;
			}
			else if(ret>0)
			{
				printf("wait success...:%d\n",ret);
				printf("exit status...:%d\n",(status>>8)&0XFF);
				printf("exit signals...:%d\n",status&0X7F);
				break;
			}
			else
			{
				sleep(1);//do other thing
				printf("father wait again! child is not exit!\n");
			}
		}
		sleep(5);
		//father
	}
	return 0;
}
