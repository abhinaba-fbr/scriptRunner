#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include "include/cleanup.h"

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

struct background_processes* bg_processes=NULL;

void init() {
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
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
        kill(bg_processes->list[i], SIGTERM);
    free(bg_processes->list);
    free(bg_processes);
    system("ip --all netns del");
    printf("Clean up Done!!\n");
    return;
}