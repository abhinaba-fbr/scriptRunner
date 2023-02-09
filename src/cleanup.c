#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include "include/cleanup.h"
#include "include/os.h"
#include "include/logging.h"

struct background_processes* bg_processes=NULL;

void signal_handler(int sig) {
    if(sig==SIGINT) {
        clean_up();
        exit(1);
    }
    else if(sig==SIGTERM) {
        clean_up();
        exit(1);
    }
}

void init(char* scriptfile, int log_status) {
    init_logging(log_status);
    change_directory(scriptfile);
    if(signal(SIGINT, signal_handler)==SIG_ERR)
        printf("scriptRunner interrupted!");
    if(signal(SIGTERM, signal_handler)==SIG_ERR)
        printf("scriptRunner terminated!");
    bg_processes=(struct background_processes*)malloc(sizeof(struct background_processes));
    bg_processes->list=(int*)malloc(sizeof(int)*100);
    bg_processes->size=0;
}

void add_background_process(int pid) {
    bg_processes->list[bg_processes->size++]=pid;
}

void clean_up() {
    // kill all background_processes
    for(int i=0;i<bg_processes->size;i++)
        killpg(bg_processes->list[i], SIGTERM);
    free(bg_processes->list);
    free(bg_processes);
    system("ip --all netns del");
    exit_logging();
    printf("Clean up Done!!\n");
    return;
}