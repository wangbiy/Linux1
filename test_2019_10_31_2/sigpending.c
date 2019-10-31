#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void show(sigset_t *pending)
{
	int i=1;
	for(;i<=31;++i)
	{
		if(sigismember(pending,i))
		{
			printf("1");
		}
		else
			printf("0");
	}
	printf("\n");
}
void handler(int sig)
{
	printf("catch signal:%d\n",sig);
}
int main()
{
	//屏蔽2号信号，获取当前pending信号，pending为000000...，然后解除阻塞时会变成010000....
	signal(2,handler);
	sigset_t set,oset;
	sigemptyset(&set);
	sigemptyset(&oset);

	sigaddset(&set,2);//将2号信号添加到set中
	sigaddset(&set,3);//将3号信号添加到set中
	sigprocmask(SIG_SETMASK,&set,&oset);
	int count=10;
	while(1)
	{
		sigset_t pending;
		sigemptyset(&pending);

		sigpending(&pending);
		show(&pending);
		sleep(1);
		//恢复回去
		//10秒后恢复信号，然后递达
		if(count--<=0)
		{
			printf("恢复signal!\n");
			sigprocmask(SIG_SETMASK,&oset,NULL);
		}

	}
	
	return 0;
}
