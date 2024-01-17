add_library(scriptRunnerlibrary STATIC
            command.c
            os.c
            cleanup.c
            logging.c
            misc.c
            types.c)

include_directories(include/)