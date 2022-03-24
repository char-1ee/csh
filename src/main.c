#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

#define TRUE 1
#define BUFF_SIZE 100

char **read_command(char *);
int cd(char *);
void sigint_handler(int);

static sigjmp_buf env;
static volatile sig_atomic_t jump_flag = 0;

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int sta_loc;

    /* Setup SIGINT */
    struct sigaction s;
    s.sa_handler = sigint_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = SA_RESTART;
    sigaction(SIGINT, &s, NULL);

    while (TRUE) {
        if (sigsetjmp(env, 1) == 42) {
            printf("\n");
            continue;
        }

        jump_flag = 1;
        input = readline("csh> ");
        if (input == NULL) {
            printf("\n");
            exit(0);
        }

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
            struct sigaction s_child;
            s_child.sa_handler = sigint_handler;
            sigemptyset(&s_child.sa_mask);
            s_child.sa_flags = SA_RESTART;
            sigaction(SIGINT, &s_child, NULL);

            /* if return -1, exxcution failed */
            if (execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            waitpid(child_pid, &sta_loc, WUNTRACED);
        }

        if (!input)
            free(input);
        if (!command)
            free(command);
    }
    return 0;
}

/* parse the input line */
char **read_command(char *input) {
    char ** command = malloc(BUFF_SIZE * sizeof(char *));

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

void sigint_handler(int signo) {
    if (!jump_flag)
        return;
    siglongjmp(env, 42);
}