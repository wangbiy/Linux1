#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
	int fd[2]={0};
	pipe(fd);
	pid_t id=fork();
	if(id==0)//child
	{

		close(fd[0]);//关闭读
		char message[]="I am a child,I am alive\n";
		while(1)
		{
			write(fd[1],message,strlen(message));
			sleep(1);

		}

	}
	else//father
	{
		close(fd[1]);
		char buf[1024];
		while(1)
		{
			size_t s=read(fd[0],buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s]=0;
				printf("I am father,got child message:%s\n",buf);
			}
			

		}
	}
	return 0;
}
