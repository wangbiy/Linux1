#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#define PATH_NAME "/tmp"
#define PROJ_ID 0x6666
#define SIZE 4097
int main()
{
	key_t k=ftok(PATH_NAME,PROJ_ID);
	if(k<0)
	{
		printf("ftok error\n");
		return 1;
	}
	int shm_id=shmget(k,SIZE,IPC_CREAT|IPC_EXCL|0644);
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
		printf("%s\n",p);
		sleep(1);
		i++;
	}
	shmdt(p);//脱离挂接
	shmctl(shm_id,IPC_RMID,NULL);//删除共享内存
	return 0;
}
