#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	if(argc < 2){
		printf("Usage %s Path_to_program", argv[0]);
		exit(-1);
	}
	char* Newargv[] = {argv[1], NULL};
	char* Newenvp[] = {NULL};
	execve(argv[1], Newargv, Newenvp);
	printf("kernal is not in the Mood :)\n");
	return -2;
}
