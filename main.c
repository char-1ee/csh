#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SH_RL_BUFSIZE 1024;

int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);

/*
    List of builtin commands, followed by their corresponding functions.
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

//------------------------------------------------------------------------------------------

/*
    Builtin function implementations.
*/
int sh_cd(char ** args) {
    if (args[1] == NULL) {      // check if 2nd argument exists

        /* TODO: can return to root dir */

        fprintf(stderr, "sh: expected argument to \" cd \" \n"); // If cd follows no PATH, report error
    } else {
        if (chdir(args[1]) != 0) {  // chdir() changes directory and checks error
            perror("sh");
        }
    }

int sh_help(char ** args) {
    int i;
    printf("Please refer to built-in commands below: \n");
    for (i = 0; i < sh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}

int sh_exit(char ** args) {
    return 0;
}

//------------------------------------------------------------------------------------------

int main(int argc, char ** argv) {      // TODO: add command hint/correction machanism? Refer to RRPSS  
    sh_loop();
    return EXIT_SUCCESS;
}

