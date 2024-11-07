#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("size %d \n", argc);
	for (int i = argc - 1; i >= 0; i--)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
}
