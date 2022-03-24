# CSH

CSH is unix shell written in c. It implements the basic functions of a unix shell, including system calls like `pwd`, `ls` and builtins like `cd`, `help`, `exit`.

## Architecture

According to *Modern Operating Systems (3rd Edition)*

```c
#define TRUE 1

while(TRUE) {                           /* repeat forever */
    type_prompt();                      /* display prompt on the screen */
    read_command(command,parameters);   /* read input from terminal */
    if(fork()!=0) {                     /* fork off child process */
        /* Parent code */
        waitpid(-1,&status,0);          /* wait for child to exit */
    } else {
        /* Child code */
        execve(command,parameters,0);   /* execute command */
    }
}
```

## Run
Compile after download the code 
```bash
$ gcc -lreadline -o code code.c
```
Then run 
```bash
$ ./csh
```

