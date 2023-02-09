# ifndef _LOGGING
# define _LOGGING
# define LOG_FILE_NAME "scriptRunner.log"
#include<stdio.h>

struct logging {
    int is_logging;
    FILE* log_file;
};

void init_logging(int);

int is_logging_allowed();

void log(char*, double);

void exit_logging();

# endif