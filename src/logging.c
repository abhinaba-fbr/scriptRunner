#include<stdio.h>
#include "include/logging.h"

struct logging* log_ops=NULL;

void init_logging(int allow) {
    log_ops=(struct logging*)malloc(sizeof(struct logging));
    log_ops->is_logging=allow;
    log_ops->log_file=fopen(LOG_FILE_NAME, "w");
}

int is_logging_allowed() {
    return log_ops->is_logging;
}

void log(char* command, double time) {command-line error: language modes specified are incompatible
    if(log_ops->allow)
        f.write(command+" "+to_string(time));
    else
        printf("Forcefull logging\n");
    return;
}

void exit_logging() {
    fclose(log_ops->log_file);
    return;
}