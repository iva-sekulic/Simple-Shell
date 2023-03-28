/* by Iva Sekulic */

#include "functions.h"

int main () {
    ssize_t read;
    long unsigned len = 0;
    pid_t pid; // pid_t represents process IDs
    char * token;
    char * argv[MAXSTR]; // user command
    char * path = "/bin/";
    char fpath[212];

    signal(SIGINT, sigintHandler);

    char * buff = NULL;

    print_function();
    fflush(stdout); // flushes the output buffer of a stream

    while ((read = getline(&buff, &len, stdin)) != -1) {

        if(read == 0)
            printf("\n");

        static int status = 0;

        if (buff[read - 1] == '\n') // strips the \n from input, this way we can use strtok()
            buff[read - 1] = '\0';

        int argc = 0;
        token = strtok(buff, delimiter); // strtok() will replace the delimiters with the NULL character   
        char * redirection_file = NULL;
        int argc_for_bracket = 0;
        while (token != NULL) {
            argv[argc] = token;
            token = strtok(NULL, delimiter);
            if(strcmp(argv[argc], ">") == 0) {
                redirection_file = token;
                argc_for_bracket = argc;
            }
            argc++;
        }

        argv[argc] = NULL;
        if(argc_for_bracket != 0) { // if > then set the NULL after
            argv[argc_for_bracket] = NULL;
        }

        if(argv[0] != NULL){ // error check - without this seg fault occurs

            if (strcmp(argv[0], "cd") == 0){      
                cd_builtin(argv);
                print_function();
            }else if ((exit_function(argv)) == 1){
                exit(0);
            } else {

            strcpy(fpath, path); // assign path to a file path
            strcat(fpath, argv[0]); // concatenate the command to the path

                pid = fork();

                if (pid == -1) {  // Fork Failed
                    perror("fork");
                    exit(1);
                } if (pid == 0) { // Child creation
                    

                    if(redirection_file != NULL) {
                        int f = open(redirection_file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
                        if (f == -1) {
                            perror("open");
                            exit(EXIT_FAILURE);
                        }
                        if (dup2(f,1) == -1){  // copying file f descriptor into stdout descriptor 
                            perror("dup2");
                        }
                    }

                    status = execvp(fpath, argv);  
                    bad_command(status);
                    exit(0);
    
                }
                    wait(NULL);  // Parent process wait for child                 
                    print_function();
               
     
            }
        }
    }
    free(buff);
    return 0;
}

