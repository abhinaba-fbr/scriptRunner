#include<string.h>
#include<ctype.h>
#include "include/types.h"

int is_blank_line(char* line) {
    size_t len=strlen(line);
    int flag=1;
    for(int i=0;i<len;i++) {
        if(line[i]=='\n') return flag;
        if(isalnum(line[i])) flag=0;
    }
    return flag;
}

int is_comment(char* line) {
    size_t len=strlen(line);
    int flag=1;
    for(int i=0;i<len;i++) {
        if(line[i]==' ') continue;
        if(line[i]=='#') return flag;
        else flag=0;
    }
    return flag;
}

int is_os_cd(char* line) {
    if(line[0]=='c' && line[1]=='d') return 1;
    else return 0;
}

int is_set_time(char* line) {
    return strstr(line, "---set-time")!=NULL;
}

int is_background(char* line) {
    return strstr(line, "---background")!=NULL;
}