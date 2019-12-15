#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <queue>
#include <string.h>
using namespace std;
#define MAX 1024
#define NUM 30
char buff[MAX];
char* argv[NUM];
std::queue<char*> q;//定义一个队列用来实现管道
void display()
{
	string tips="[XXX@localhost YYY]$";
	cout<<tips;//打印提示信息
	fgets(buff,MAX,stdin);//从标准输入拿到命令行放入buff中
	buff[strlen(buff)-1]=0;//将\n设为0，防止回车之后多出一行
}
//解析命令行
void analy(char* pbuff)
{
	int i=0;
	argv[0]=strtok(pbuff," ");//按照空格分隔
	while(argv[i]!=NULL)
	{
		i++;
		argv[i]=strtok(NULL," ");
	}
}
std::queue<char*>& pipe_num()//实现管道，判断是否有管道符，具有连接两个命令的作用，遇到管道符，就置为\0，然后入队，使用时从队列中取出即可
{
	while(!q.empty())
	{
		q.pop();
	}
	char* ptr=buff;
	q.push(ptr);
	while(*ptr!='\0')
	{
		if(*ptr=='|')
		{
			*ptr='\0';
			ptr++;
			while(*ptr==' ')
			{
				ptr++;
			}
			q.push(ptr);
		}
		ptr++;
	}
	return q;
}
//重定向
void diredict(char* buf)
{
	char* ptr=buf;
	char* file=NULL;
	int flag=0;//1--清空重定向，2---追加
	int fd;
	while(*ptr!='\0')
	{
		if(*ptr=='>')
		{
			*ptr='\0';
			flag=1;
			ptr++;
			if(*ptr=='>')
			{
				flag=2;
				ptr++;
			}
			while((*ptr!=' ')&&(*ptr!='\0'))//将>符号后的空白字符走完，直到文件名的起始位置
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
	if(flag==1)
	{
		fd=open(file,O_CREAT|O_WRONLY| O_TRUNC,0644);
		dup2(fd,1);//重定向的文件描述符不会随着程序而初始化
	}
	else if(flag==2)
	{
		fd=open(file,O_CREAT|O_WRONLY| O_APPEND,0644);
		dup2(fd,1);//重定向的文件描述符不会随着程序而初始化
	}
	close(fd);
}
//进程替换
void do_fork(std::queue<char*>& q)
{
	while(!q.empty())
	{
		pid_t id=fork();
		if(id<0)
		{
			cout<<"fork error"<<endl;
		}
		else if(id==0)//child
		{
			char* tmp=q.front();
			diredict(tmp);
			analy(tmp);
			execvp(argv[0],argv);
		}
		else
		{
			waitpid(id,NULL,0);
		}
		q.pop();
	}
}
int main()
{
	while(1)
	{
		display();
		std::queue<char*>& q_pipe=pipe_num();
		do_fork(q_pipe);
		sleep(1);
	}
	return 0;
}


	
	


