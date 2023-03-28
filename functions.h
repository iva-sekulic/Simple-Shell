/* by Iva Sekulic */

#define MAXSTR 512
#define delimiter " "
#define EXIT "exit"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

void function_time(void);

void sigintHandler();

void cd_builtin(char **argv);

int bad_command(int status);

int exit_function(char **argv);

void print_function();