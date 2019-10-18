#include <stdio.h>
#include <stdlib.h>
//int main()
//{
//	printf("%s\n",getenv("MYENV"));
//	return 0;
//}
/*int g_val=100;
  int main()
  {
  pid_t id=fork();
  if(id==0)
  {
  sleep(1);
  g_val=200;
  printf("child: %d,%p\n",g_val,&g_val);
  }
  else
  {
  sleep(2);
  printf("father:%d,%p\n",g_val,&g_val);
  }
  return 0;
  }*/
/*void test()
  {
  exit(21);
  }
  int main()
  {
  printf("hello bit!\n");
  test();
  while(1)
  {

  printf("----------\n");
  }
  }*/
#include <unistd.h>
/*int main()
  {
  printf("hello bit");
  sleep(3);
  _exit(32);	
  }*/
void my_malloc(int** p)//p是输出型参数
{
	*p=(int*)malloc(10*sizeof(int));
}
int main()
{
	int* p=NULL;
	my_malloc(&p);
	p[1]=10;
}
