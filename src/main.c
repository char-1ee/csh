#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

#define TRUE 1
#define BUFF_SIZE 100

char **read_command(char *);
int cd(chat *);

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int sta_loc;

    while (TRUE) {
        input = readline("csh> ");
        command = read_command(input);

        /* handle empty command */
        if (!command[0]) {
            free(input);
            free(command);
            continue;
        }

        /* run cd in parent process */
        if (strcmp(command[0], "cd") == 0) {
            if (cd(command[1]) < 0) {
                perror(command[1]);
            }
            continue;
        }

        /* start child process */
        child_pid = fork();

        /* if OS run out of memory */
        if (child_pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (child_pid == 0) {

            /* if return -1, exxcution failed */
            if (execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            waitpid(child_pid, &sta_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }
    return 0;
}

/* parse the input line */
char **read_command(char *input) {
    char ** command = malloc(BUFF_SIZE * sizeof(char *)));

    /* if OS run out of memory */
    if (command == NULL) {
        perror("malloc failed");
        exit(1);
    }

    char *delim = " ";
    char *tokens;
    int index = 0;

    tokens = strtok(input, delim);
    while (tokens != NULL) {
        command[index] = tokens;
        index++;

        while (tokens = strtok(NULL, delim))
            ;
    }
    command[index] = NULL;
    return command;
}

/* builtin cd needs we implement it on our own */
int cd(char *path) {
    return chdir(path);
}