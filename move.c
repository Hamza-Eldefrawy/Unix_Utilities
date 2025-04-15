#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	char buf[100];
	if(argc != 3)
	{
		printf("Usage: %s /Soruce /Distenation\n", argv[0]);
		exit(-1);
	}
	else
	{
		return rename(argv[1], argv[2]);
	}
	
}
