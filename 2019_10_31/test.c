#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
void handler(int signo)
{
	printf("catch a sig:%d\n",signo);
	exit(1);
}
int main()
{
	int i=1;
	while(i<=31)
	{
		signal(i++,handler);
	}
	int *p=NULL;
	*p=100;
	return 0;
}


//信号捕捉函数signal
//int main()
//{
//	signal(2,handler);
//	while(1);
//	return 0;
//}
//int main()
//{
//	//kill(getpid(),3);//发送3号信号,也可以使用这个信号的宏名称
//	//raise(SIGQUIT);
//	abort();
//
//	//alarm(2);
//	while(1)
//	{
//		printf("-------\n");
//	}
//	return 0;
//}
