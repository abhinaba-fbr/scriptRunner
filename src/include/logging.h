# ifndef _LOGGING
# define _LOGGING
#include<stdio.h>

struct logging {
    int is_logging;
    FILE* log_file;
};

void init_logging(int, char*);

int is_logging_allowed();

void Log(char*, double);

void exit_logging();

# endif