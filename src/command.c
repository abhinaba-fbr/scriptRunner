#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>
#include "include/types.h"
#include "include/misc.h"
#include "include/os.h"
#include "include/cleanup.h"
#include "include/command.h"
#include "include/logging.h"

void parse_command(void* cmd_args) {
    struct command_args* cmd=(struct command_args*)cmd_args;
    cmd->time=0;
    cmd->len=strlen(cmd->command);
    cmd->type=NORMAL;
    // Ignore process
    if(is_blank_line(cmd->command) || is_comment(cmd->command)) {
        cmd->type=IGNORE;
    }
    // OS process
    else if(is_os_cd(cmd->command)) {
        cmd->type=OS;
        cmd->len=strlen(cmd->command);
    }
    // Time process or Time wait process
    else if(is_set_time(cmd->command) || is_set_time_wait(cmd->command)) {
        if(is_set_time_wait(cmd->command)) cmd->type=TIME_WAIT;
        else cmd->type=TIME;
        int pos=strstr(cmd->command, "---set-time") - cmd->command;
        int time=0;
        for(int i=pos;i<cmd->len;i++) {
            if(isdigit(cmd->command[i])) {
                time=time*10+(to_int(cmd->command[i]));
            }
        }
        char* new_command=(char*)malloc(sizeof(char)*pos);
        strncpy(new_command, cmd->command, pos);
        free(cmd->command);
        cmd->command=new_command;
        cmd->time=time;
        cmd->len=strlen(cmd->command);
    }
    // Background process
    else if(is_background(cmd->command)) {
        cmd->type=BACKGROUND;
        int pos=strstr(cmd->command, "---background") - cmd->command;
        char* new_command=(char*)malloc(sizeof(char)*(pos+1));
        strncpy(new_command, cmd->command, pos);
        free(cmd->command);
        cmd->command=new_command;
        cmd->len=strlen(cmd->command);
    }
    return;
}

void execute_command(void* cmd_args) {
    struct command_args* cmd=(struct command_args*)cmd_args;
    time_t start_time=time(NULL);
    pid_t pid=getpid();
    // Ignore process
    if(cmd->type==IGNORE)  {
        return;
    }
    // OS process
    else if(cmd->type==OS) {
        change_directory(cmd->command);
    }
    // Time process or Time wait process
    else if(cmd->type==TIME || cmd->type==TIME_WAIT) {
        pid=fork();
        if(pid==0) {
            sleep(cmd->time);
            execl(INTERPRETER, INTERPRETER, "-c", cmd->command, NULL);
            exit(0);
        }
        else if(pid>0) {
            if(cmd->type==TIME_WAIT) waitpid(pid, NULL, 0);
            else add_background_process(getpgid(pid));
        }
        else
            perror("Failed to fork() child");
    }
    // Background process
    else if(cmd->type==BACKGROUND) {
        pid=fork();
        if(pid==0) {
            sleep(cmd->time);
            execl(INTERPRETER, INTERPRETER, "-c", cmd->command, NULL);
            exit(0);
        }
        else if(pid>0) 
            add_background_process(getpgid(pid));
        else
            perror("Failed to fork() child");
    }
    // Normal process
    else {
        pid=fork();
        if(pid==0) {
            execl(INTERPRETER, INTERPRETER, "-c", cmd->command, NULL);
            exit(0);
        }
        else if(pid>0) 
            waitpid(pid, NULL, 0);
        else
            perror("failed to fork() child");
    }
    time_t end_time=time(NULL);
    if(is_logging_allowed())
        Log(cmd->command, (end_time-start_time));
    return;   
}