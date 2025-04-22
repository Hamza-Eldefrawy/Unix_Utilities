#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define buf_size 100

typedef struct {
    char *key;
    char *value;
    int exported;
} Variable;

Variable *variables = NULL;
int var_count = 0;

void free_variables() {
    for (int i = 0; i < var_count; i++) {
        free(variables[i].key);
        free(variables[i].value);
    }
    free(variables);
}

void export_variable(const char *key) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].key, key) == 0) {
            variables[i].exported = 1;
            
            char *env_str = malloc(strlen(key) + strlen(variables[i].value) + 2);
            sprintf(env_str, "%s=%s", key, variables[i].value);
            putenv(env_str);

            return;
        }
    }
    printf("Variable not found\n");
}

void add_variable(const char *key, const char *value) {
    // Check if variable already exists
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].key, key) == 0) {
            free(variables[i].value);
            variables[i].value = strdup(value);
            return;
        }
    }

    // Allocate more space
    variables = realloc(variables, sizeof(Variable) * (var_count + 1));
    
    // Add the new variable
    variables[var_count].key = strdup(key);
    variables[var_count].value = strdup(value);
    variables[var_count].exported = 0;
    var_count++;
}


int main() {

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
			
//===================== handle the local variables =====================\\

        char *x = strchr(buf, '=');
        if(x != NULL)
        {
            char *key;
            if(strchr(buf, ' ') == NULL)
            {
                int len = x - buf;
                key = buf;
                key[len] = 0;
                add_variable(key, x + 1);
            }
            else
            {
                printf("Invalid command\n");
            }
            continue;
        }
        
        char *dollar = strchr(buf, '$'); 
        if (dollar) 
        {
            char *a = buf;
            a[dollar - buf] = 0;
            char *key = dollar + 1;
            for(int i = 0; i < var_count; i++)
            {
                if(strcmp(variables[i].key, key) == 0)
                {
                    key = variables[i].value;
		    sprintf(buf, "%s%s", a, key);
                }
		else
		    sprintf(buf, "%s", a);
            }
        }
//=======================================================================\\

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
		
		//5th: export
		else if (strcmp(cmd, "export") == 0) {
			char *rest = strtok(NULL, "");
            export_variable(rest);
		}
		
		//6th: otherwise(usint fork & exec syscalls)
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
				newargs[i] = NULL;
				execvp(cmd, newargs);
				printf("Execution failed\n");
				exit(-1);
			}
		}
	}
    free_variables();
	return 0;
}
