#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc < 2)
		printf("Should I print from my mind?\n");
	else
	{
		for(int i = 1; i < argc; i++){
			printf("%s ", argv[i]);
		}
		printf("\n");
	}
	return 0;
}
