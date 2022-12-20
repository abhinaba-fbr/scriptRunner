# ifndef _COMMAND_ARGS
# define _COMMAND_ARGS

# include "types.h"

struct command_args {
    char* command;
    int time;
    size_t len;
    COMMAND_TYPE type; 
};

void parse_command(void* cmd_args);

void execute_command(void* cmd_args);

# endif