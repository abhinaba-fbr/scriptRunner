#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include "include/cleanup.h"
#include "include/command.h"
#include "include/os.h"

/*
    To Do -
    1. Imporve get_file_path API (in os.h)
*/

// Main function

int main(int argc, char **argv) {
    int status=0;
    int log_status=0;
    char* scriptfile;
    if(argc<2) {
        printf("Error! Input file not provided\n");
        status=1;
        goto exit_label;
        exit_error_label:
            exit(1);
    }
    else if(argc==2) {
        if(strstr(argv[1], "---logging")){
            printf("Error! Input file not provided\n");
            status=1;
            goto exit_label;
        }
        scriptfile=(char*)malloc(sizeof(char)*strlen(argv[1]));
        strcpy(scriptfile, argv[1]);
    }
    else if(argc==3) {
        if(strstr(argv[1], "---logging")) {
            scriptfile=(char*)malloc(sizeof(char)*strlen(argv[1]));
            strcpy(scriptfile, argv[1]);
        }
        else {
            scriptfile=(char*)malloc(sizeof(char)*strlen(argv[2]));
            strcpy(scriptfile, argv[2]);
        }
    }
    else {
        printf("Error! argument not recognized\n");
        status=1;
        goto exit_label;
    }

    init(scriptfile, log_status);
    FILE *file;
    file=fopen(scriptfile, "r");
    if(file==NULL) {
        perror("Error! script file failed to open");
        status=1;
        goto exit_label;
    }

    char* input_line=NULL;
    size_t len=0;
    while(getline(&input_line, &len, file)!=EOF) {
        struct command_args* cmd=(struct command_args*)malloc(sizeof(struct command_args));
        if(cmd==NULL) {
            perror("Error! allocating memory");
            status=1;
            fclose(file);
            goto exit_label;
        }
        cmd->command=(char*)malloc(strlen(input_line)*sizeof(char));
        strcpy(cmd->command, input_line);
        parse_command(cmd);
        input_line=NULL;
        len=0;
        fflush(file);
        fflush(stdout);
        execute_command(cmd);
    }

    fclose(file);
    printf("Closing experiment!!\n");
    exit_label:
    clean_up();
    if(status)
        goto exit_error_label;
    return 0;
}