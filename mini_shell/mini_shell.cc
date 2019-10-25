#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
using namespace std;
#define NUM 32
int main()
{
	char buff[1024]={0};
	while(1)//因为要能循环输入命令，所以使用for循环
	{
		string tips="[XXX@localhost YYY]#";//定义一个提示输入命令，与系统默认的不同即可
		cout<<tips;
		fgets(buff,sizeof(buff)-1,stdin);//从外设拿到输入的信息
		buff[strlen(buff)-1]=0;//将\n设为0，防止在输入命令后回车运行，结果也会出现一个回车空行


		char* argv[NUM];//拿到输入的命令
		argv[0]=strtok(buff," ");//因为命令行是用空格分隔的，因此这里使用strtok进行分隔，argv[0]放命令的首地址
		int i=0;
		while(argv[i]!=NULL)//使用循环分别拿到空格分隔的命令，例如ls -a要分别拿到ls 和-a
		{
			i++;
			argv[i]=strtok(NULL," ");
		}
		//实现重定向
		char* ptr=NULL;
		ptr=buff;
		char* file=NULL;
		int flag = 0;
		while(*ptr!='\0')
		{
			if(*ptr=='>')
			{
				*ptr='\0';
				ptr++;
				flag=1;
				//继续往后看是不是追加重定向
				if(*ptr == '>')
				{
					*ptr='\0';
					ptr++;
					flag=2;
				}

				while(*ptr==' ')
				{
					ptr++;
				}
				file=ptr;
				while((*ptr!=' ')&&(*ptr!='\0'))
				{
					ptr++;
				}
				*ptr='\0';
			}
			ptr++;
		}
		//开始进行命令运行后的显示结果
		pid_t id=fork();
		if(id==0)
		{
			int fd=1;
			if(flag==1)
			{
				fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);
			}
			else if(flag==2)//追加重定向
			{
				fd=open(file,O_CREAT|O_APPEND|O_WRONLY,0644);
			}
			dup2(fd,1);

			execvp(argv[0],argv);//使用替换函数
			//argv[0]表示拿到外设输入的第一个命令的程序名，例如输入ls -a就是拿到ls这个程序名,后面的argv表示将可变参数列表封装成argv，它会自动搜索环境变量
			exit(123);//表示替换函数调用失败
		}
		else
		{
			int status=0;
			waitpid(id,&status,0);//父进程进行等待，获得子进程的id，子进程退出状态，将父进程设为0也就是阻塞状态
			cout<<"Exit code:"<<WEXITSTATUS(status)<<endl;
		}
	}
	return 0;
}
