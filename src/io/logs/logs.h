#ifndef LOGS
#define LOGS
#include "../../utils/dynamic-array.h"
// log format : ex "2026/07/07 new request" 
#define DATE_LENGTH 10
#define FIRST_MESSAGE_INDERX_POSITION 11
void extract_logs(HistoryArray *history_arr, char *path);
#endif