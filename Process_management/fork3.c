#include <stdio.h>
#include <unistd.h>

int x = 5;
int y;

int main()
{
	int z = 10;
	getchar();
	
	x++; y++; z++;
	printf("PARENT: before fork x= %d, y=%d, z=%d\n", x, y, z);
	pid_t pid = fork();
	if (pid > 0)
	{
		while(1){
			printf("Parent: my PID = %d, my child PID = %d\n", getpid(), pid);
			printf("Parent: after fork x= %d, y=%d, z=%d\n", x, y, z);
			x++; y++; z++;
			usleep(500000);
		}
	}
	else if (pid == 0)
	{
		while(1){
			printf("Child: my PID = %d, my parent PID = %d\n", getpid(), getppid());
			printf("Child: after fork x= %d, y=%d, z=%d\n", x, y, z);
			x++; y++; z++;
			x++; y++; z++;
			x++; y++; z++;
			usleep(500000);
		}
	}
	else
	{
		printf("Fork faild");
	}

	getchar();
	return 0;
}
