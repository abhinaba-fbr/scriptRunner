# ifndef _CLEAN_UP
# define _CLEAN_UP

#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

struct background_processes {
    int* list;
    int size;
};

void init();

void add_background_process(int pid);

void clean_up();

# endif 