#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    char input[1024];
    char *command;
    
    while(1){
        
        //prompt
        printf("أؤمر معلم بدك ياه لحمة ولا جاج؟");
        printf(" > ");
        
        //
        if(fgets(input, sizeof(input), stdin) == NULL){
            continue;
        }
        
        //
        input[strcspn(input, "\n")] = '\0';
        command = strtok(input, " ");
        
        //
        if(strcmp(command, "exit") == 0){
            printf("Good Bye\n");
            break;
        }
        
        //
        if(command != NULL && strcmp(command, "echo") == 0){
            char *rest = input + strlen(command) + 1;
            if(rest != NULL)
                printf("%s\n", rest);
            else
                printf("\n");
        }
        else
            printf("Invalid command\n");
    }
    return 0;
}
