#ifndef  DAYNAMIC_ARRAY
#define DAYNAMIC_ARRAY

typedef struct {
    char *date;
    char *message;
}History ;

typedef struct HistoryArray {
    History **history;    
    int length;
    void (*add_history_log) (struct HistoryArray *str_arr, char *date, char *message);
    void (*remove_history_log) (struct HistoryArray *history_arr);
} HistoryArray ;

void add_history_log(HistoryArray *history_arr, char *date, char *message);
#endif