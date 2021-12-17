#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SH_RL_BUFSIZE 1024;

int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);

/**
 * @brief List of builtin commands, followed by their corresponding functions. 
 */
char * builtin_str[] = {
    "cd", 
    "help", 
    "exit"
};

int (* builtin_func[]) (char **) = {
    &sh_cd,
    &sh_exit,
    &sh_help
};

int sh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/**
 * @brief Built-in shell commands: cd.
 */
int sh_cd(char ** args) {

    // check if 2nd argument exists
    if (args[1] == NULL) {

        /* TODO: can return to root dir */

        // If cd follows no PATH, report error
        fprintf(stderr, "sh: expected argument to \" cd \" \n"); 

    } else {

        // chdir() changes directory and checks error
        if (chdir(args[1]) != 0) {
            perror("sh");
        }
    }

/**
 * @brief Built-in shell command: help.
 */
int sh_help(char ** args) {
    int i;
    printf("Please refer to built-in commands below: \n");
    for (i = 0; i < sh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}

/**
 * @brief Built-in shell command: exit.
 */
int sh_exit(char ** args) {
    return 0;
}

/**
 * @brief Reading a line.
 */
char * sh_read_line(void) {
    int buffsize = SH_RL_BUFSIZE;
    int position = 0;
    int c;
    char * buffer = malloc(sizeof(char) * buffsize);

    if (!buffer) {
        fprintf(stderr, "sh: intial allocation error \n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // read a charactor
        c = getchar();

        // when hit EOF or escape, replace it with null charactor and return
        if (c == EOF || c = '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
    }   

    // a common strategy: when exceed buffersize, we reallocate the buffer
    if (position >= buffsize) {
        buffsize += SH_RL_BUFSIZE;
        buffer = realloc(buffer, buffersize);
        if (!buffer) {
            fprintf(stderr. "sh: reallocation error \n");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Parsing the line. 
 * 
 */

// TODO


/**
 * @brief Putting together builtins and processes.
 * 
 * @param args 
 * @return int 
 */
int sh_execute(char ** args) {
    int i;

    // an empty command was entered
    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < sh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[0]) == 0)
            return (*builtin_func[i])(args);
    }

    return sh_launch(args);
}

// TODO
int sh_launch(char ** args) {
    pid_t pis, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        id ()
    }
}

/**
 * @brief A loop to input.
 * 
 */
void sh_loop(void) {
    char * line;
    char ** args;
    int status;

    do {
        printf("> ");
        line = sh_read_line();
        args = sh_split_line(line);
        status = sh_execute(args);

        free(line);
        free(args);
    } while (status)
}

int main(int argc, char ** argv) {      // TODO: add command hint/correction machanism? Refer to RRPSS  
    
    // Run command loop
    sh_loop();

    return EXIT_SUCCESS;
}

