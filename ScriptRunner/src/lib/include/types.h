# ifndef _TYPES
# define _TYPES
# define INTERPRETER "/bin/sh"

typedef enum COMMAND_TYPE {
    NORMAL,
    IGNORE,
    OS,
    TIME,
    TIME_WAIT,
    BACKGROUND
} COMMAND_TYPE;

int is_blank_line(char* line);

int is_comment(char* line);

int is_os_cd(char* line);

int is_set_time(char* line);

int is_set_time_wait(char* line);

int is_background(char* line);

# endif