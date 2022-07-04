# csh

This is a simplified Unix shell in C. It implements part of bash built-in commands (`pwd`, `ls`, `help` etc.) and supports singals and error handling.

### Basic logic
According to *Modern Operating Systems (3rd Edition)*:
```c
#define TRUE 1

while (TRUE) {                           /* repeat forever */
    type_prompt();                      /* display prompt on the screen */
    read_command(command, parameters);   /* read input from terminal */
    if (fork() != 0) {                     /* fork off child process */
        /* Parent code */
        waitpid(-1, &status, 0);          /* wait for child to exit */
    } else {
        /* Child code */
        execve(command, parameters, 0);   /* execute command */
    }
}
```

### Run
On Debian based platforms, like Ubuntu, prerequisite for `readline/readline.h`:
```bash
$ sudo apt-get install libreadline-dev 
```
Then build with Makefile:
```bash
$ git clone https://github.com/char-1ee/csh.git
$ cd csh
$ make
```
