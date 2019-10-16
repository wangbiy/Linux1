#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t id=fork();
	if(id<0)
	{
		perror("fork");
	}
	else if(id==0)//child
	{
		printf("I am a child : pid:%d ppid:%d\n",getpid(),getppid());
	}
	else//father
		printf("I am a parent : pid:%d ppid:%d\n",getpid(),getppid());
	sleep(1);
}
