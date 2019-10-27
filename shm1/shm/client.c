#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#define PATH_NAME "/tmp"
#define PROJ_ID 0x6666
#define SIZE 4096
int main()
{
	key_t k=ftok(PATH_NAME,PROJ_ID);
	if(k<0)
	{
		printf("ftok error\n");
		return 1;
	}
	int shm_id=shmget(k,SIZE,0);//此时客户端不用创建共享内存，只用获取即可
	if(shm_id<0)
	{
		printf("shmget error!\n");
		return 2;//错误码设置为2
	}
	//挂接
	char* p=(char*)shmat(shm_id,NULL,0);
	int i=0;
	while(i<SIZE)
	{
		p[i]='a'+i;
		i++;
		p[i]=0;
		sleep(1);
	}
	shmdt(p);//脱离挂接
	//不需要删除共享内存，因为他没有创建共享内存，所以不用删除
	return 0;
}
