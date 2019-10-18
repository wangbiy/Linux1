#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	char* const envp[]={"PATH=/bin:/usr/bin","TERM=console",NULL};
	char* const argv[]={"ps","-ef",NULL};
	//execle("/usr/bin/ps","ps","-ef",NULL,envp);
	execve("/usr/bin/ps",argv,envp);
	exit(0);
	return 0;
}
/*{
  int i=0;
  for(;i<10;++i)
  {
  printf("hello :%d\n",i);
  }
  return 0;
  }*/

