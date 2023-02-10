#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "include/logging.h"

struct logging* log_ops=NULL;

void init_logging(int allow, char* log_file) {
    log_ops=(struct logging*)malloc(sizeof(struct logging));
    log_ops->is_logging=allow;
    if(log_ops->is_logging) {
        if(strstr(log_file, "---logging=")) {
            int length=strlen(log_file);
            int pos=strstr(log_file, "=") - log_file;
            char* log_file_name=(char*)malloc(sizeof(char)*(length-pos-1));
            strncpy(log_file_name, log_file+pos+1, (length-pos-1));
            log_ops->log_file=fopen(log_file_name, "w");
        }
        else {
            log_ops->log_file=fopen("scriptRunner.log", "w");
        }
    }
}

int is_logging_allowed() {
    return log_ops->is_logging;
}

void Log(char* command, double time) {
    size_t len=strlen(command);
    if(command[len-1]=='\n')
        command[len-1]='\0';
    fprintf(log_ops->log_file, "%s @time@ %f\n", command, time);
    fflush(log_ops->log_file);
    return;
}

void exit_logging() {
    if(log_ops->is_logging)
        fclose(log_ops->log_file);
    return;
}