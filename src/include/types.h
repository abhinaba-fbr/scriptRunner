# ifndef _TYPES
# define _TYPES

typedef enum COMMAND_TYPE {
    NORMAL,
    IGNORE,
    OS,
    TIME,
    BACKGROUND
} COMMAND_TYPE;

int is_blank_line(char* line);

int is_comment(char* line);

int is_os_cd(char* line);

int is_set_time(char* line);

int is_background(char* line);

# endif