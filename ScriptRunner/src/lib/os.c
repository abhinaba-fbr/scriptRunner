#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "include/os.h"

char* _get_file_path(char* path) {
    unsigned int len=strlen(path);
    unsigned int beg=0, end=0;
    unsigned int has_file=0;
    if(path[0]=='c' && path[1]=='d')
        beg=2;
    while(path[beg]==' ')
        beg++;
    end=beg;
    for(int i=beg;i<len;i++) {
        if(path[i]=='/') end=i;  
    }
    for(int i=len-1;i>end;i--) {
        if(path[i]=='.') {
            has_file=1;
        }
    }
    char* new_path=NULL;
    if(has_file && beg==end) {
        new_path=(char*)malloc(sizeof(char)*2);
        new_path[0]='.';
        new_path[1]='/';
        return new_path;
    }
    unsigned int size=(has_file)?end-beg:len-beg-1;
    new_path=(char*)malloc(sizeof(char)*size);
    for(int i=beg, j=0;j<size;i++, j++) {
        new_path[j]=path[i];
    }
    return new_path;
}

void change_directory(char* path) {
    char* pathname=_get_file_path(path);
    if(chdir(pathname)!=0) 
        perror("chdir() failed");
    free(pathname);
    return;
}