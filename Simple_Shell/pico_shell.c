#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define buf_size 100

int main(int argc, char *argv[])
{

	char buf[buf_size];
	char *cmd;

	while (1) {
		//funny prompt
		printf("Your Gennie is between your hand $ ");
		fflush(stdout);

		//read input from user
		fgets(buf, buf_size, stdin);

		//terminate the input at the new line
		buf[strlen(buf) - 1] = 0;

		//check if the input is empty
		if (strlen(buf) == 0)
			continue;

		//extract the command
		cmd = strtok(buf, " ");

		//1st: exit
		if (strcmp(cmd, "exit") == 0) {
			printf("\nGood Bye\n");
			break;
		}
		//2nd: pwd
		else if (strcmp(cmd, "pwd") == 0) {
			char path[PATH_MAX];
			if (getcwd(path, sizeof(path)) != NULL)
				printf("%s\n", path);
			else
				perror("pwd");
		}
		//3rd: cd
		else if (strcmp(cmd, "cd") == 0) {
			char *path = strtok(NULL, "");
			if (path == NULL)
				fprintf(stderr, "cd: missing argument\n");
			else {
				if (chdir(path) != 0)
					perror("cd");
			}
		}
		//4th: echo
		else if (strcmp(cmd, "echo") == 0) {
			char *rest = strtok(NULL, "");
			if (rest != NULL)
				printf("%s\n", rest);
			else
				printf("\n");
		}
		//5th: otherwise(usint fork & exec syscalls)
		else {
			pid_t pid = fork();
			if (pid > 0) {
				int status;
				waitpid(pid, &status, 0);
			} else if (pid == 0) {
				char *newargs[buf_size];
				int i = 0;
				newargs[i++] = cmd;
				char *token;
				while ((token = strtok(NULL, " ")) != NULL) {
					newargs[i++] = token;
				}
				execvp(cmd, newargs);
				printf("Execution failed");
				exit(-1);
			}
		}
	}
	return 0;
}
