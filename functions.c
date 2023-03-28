/* by Iva Sekulic */

#include "functions.h"

void function_time(void) {
    time_t rawtime;
    char buffer[26];
    struct tm * info;

    rawtime = time(NULL);
    info = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d/%m %H:%M", info);
    printf("[%s]", buffer);
}

void print_function() {
    printf("\033[1;35m"); //sets the prompt colour to pink
    function_time();
    printf("#");
    printf("\033[0m"); //returns to default colour 
}

void sigintHandler(int signo) {
    printf("\n");
    print_function();
    fflush(stdout);

}

int bad_command(int status){
    if (status == -1)
        printf("Command not found.\n");
}

void cd_builtin(char **argv) {
    if(argv[1] == NULL){
        chdir(getenv("HOME"));
        if (chdir(getenv("HOME")) == -1) {
            perror("Home not found");
        } 
    }else{
        if (chdir(argv[1]) == -1) {
            fprintf(stderr, "cd: %s: ", argv[1]);
            perror("");
        } 
    }
}

int exit_function(char **argv) {
    if(strcmp(argv[0], EXIT) == 0)
        return 1;
}

