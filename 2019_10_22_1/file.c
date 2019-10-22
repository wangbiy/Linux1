//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//int main()
//{
//    pid_t id=fork();
//    if(id<0)
//     {
//         perror("fork");
//     }
//     else if(id==0)//child
//     {
//         printf("I am child,begin Z+,pid=%d,ppid=%d\n",getpid(),getppid());
//         sleep(5);
//         exit(0);
//     }
//     else
//      {
//          printf("I am father,pid=%d,ppid=%d\n",getpid(),getppid());
//          sleep(30);
//      }
//    return 0;
//}
//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//	printf("%s\n",getenv("PATH"));
//	return 0;
//}
//#include <stdio.h>
//int main(int argc,char* argv[],char* env[])
//{
//	int i=0;
//	for(;i<10;++i)
//		printf("%d:%s\n",i,env[i]);
//
//	return 0;
//}
//int main()
//{
//	extern char** environ;
//	int i=0;
//	for(;i<10;++i)
//		printf("%s\n",environ[i]);
//	return 0;
//}
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
int main()
{
	pid_t id=fork();
	if(id==0)//child
	{
		printf("I am child,pid:%d,ppid:%d\n",getpid(),getppid());
		sleep(10);
		exit(13);
	}
	else

	{
		printf("I am father,pid:%d,ppid:%d\n",getpid(),getppid());
		int status = 0;
		sleep(15);
		int ret=waitpid(id,&status,0);
		if(ret<0)
		{
			printf("wait error....,ret:%d\n",ret);
		}
		else
		{
			printf("wait success...%d\n",ret);
			printf("exit status....%d\n",(status>>8)&(0xff));
			printf("exit signals...%d\n",status&0x7f);
		}
		sleep(5);
	}
	return 0;
}
