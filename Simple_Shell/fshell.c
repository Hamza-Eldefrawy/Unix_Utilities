#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char input[10240];
    char *cmd;

    while (1) {
        
        // prompt
        printf("أؤمر معلم بدك ياه لحمة ولا جاج؟ > ");

        // read input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            return 0;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        // skip empty
        if (strlen(input) == 0) {
            printf("\n");
            continue;
        }

        // extract command manually
        cmd = strtok(input, " ");   

        //
        if (strcmp(cmd, "exit") == 0) {
            printf("\nGood Bye\n");
            return 0;
        } else if (strcmp(cmd, "echo") == 0) {
            char *rest = input + strlen(cmd) + 1;
            if(rest != NULL)
                printf("\n%s\n", rest);
            else
                printf("\n");
        } else{
            printf("\nInvalid command\n");
        }
    }

    return 0;
}
