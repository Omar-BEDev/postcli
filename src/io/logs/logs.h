#ifndef LOGS
#define LOGS
#include "../../utils/dynamic-array.h"
#include <stdio.h>
#include <string.h>


// log format : ex "2026/07/07 new request" 
#define DATE_LENGTH 10
#define FIRST_MESSAGE_INDERX_POSITION 11

void extract_logs(HistoryArray *history_arr, char *path);

#if defined (__linux__)
    #include "sys/stat.h"
    #include "sys/types.h"
    #define LINUX_HOME_DIR getenv("HOME")
    #define make_folder(dir) mkdir(dir, 0755)  
#endif

void log_path_generate(char *dir);
#endif