#include "my_add.h"
#include "my_sub.h"
#include "my_mul.h"
#include "my_div.h"
#include <stdio.h>
int main()
{
	printf("Please Enter:");
	printf("%d\n",my_add(1,2));
	printf("%d\n",my_sub(1,2));
	printf("%d\n",my_mul(1,2));
	printf("%d\n",my_div(1,2));
	return 0;
}

