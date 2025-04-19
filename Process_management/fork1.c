#include <stdio.h>
#include <unistd.h>

int main()
{
	getchar();
	
	pid_t pid = fork();
	if (pid > 0)
	{
		printf("Parent: my PID = %d, my child PID = %d\n", getpid(), pid);
	}
	else if (pid == 0)
	{
		printf("Child: my PID = %d, my parent PID = %d\n", getpid(), getppid());
	}
	else
	{
		printf("Fork faild");
	}

	getchar();
	return 0;
}
