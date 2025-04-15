#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc > 1)
		printf("Wrong usage, No arguments needed\n");
	else
	{
		char buff[PATH_MAX];
		if(getcwd(buff, PATH_MAX) != NULL){
			printf("Working directory: %s\n", buff);
		}
		else
			exit(1);
	}
	return 0;
}
