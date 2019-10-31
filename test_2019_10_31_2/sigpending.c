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
int main()
{
	//屏蔽2号信号，获取当前pending信号，pending为000000...，然后解除阻塞时会变成010000....
	sigset_t set,oset;
	sigemptyset(&set);
	sigemptyset(&oset);

	sigaddset(&set,2);//将2号信号添加到set中
	sigaddset(&set,3);//将3号信号添加到set中
	sigprocmask(SIG_SETMASK,&set,&oset);

	while(1)
	{
		sigset_t pending;
		sigemptyset(&pending);

		sigpending(&pending);
		show(&pending);
		sleep(1);
	}
	return 0;
}
