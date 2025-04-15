#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * step 1: open the file that will be copied
 * step 2: read the file
 * step 3: write on the file if it exist or create it first  
 */

int main(int argc, char** argv) // ./copy path_to_file path_to_copied
{
	char buf[100];
	if(argc != 3)
	{
		printf("Usage: %s /file_to_be_copied_from /file_to_be_copied_to\n", argv[0]);
		exit(-1);
	}
	int fd0 = open(argv[1], O_RDONLY);
	if(fd0 < 0)
	{
		printf("could not open a file\n");
		exit(-2);
	}
	int num_read;
	int fd1 = open(argv[2], O_WRONLY | O_CREAT, 0644);
	while((num_read = read(fd0, buf, 100)) > 0)
	{
 	 if(write(fd1, buf, num_read) < 0)
	 {
	 	printf("Write failed\n");
	 	exit(-3);
	 }
	}
	close(fd0);
	close(fd1);
	return num_read;
}
