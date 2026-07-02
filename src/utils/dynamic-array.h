#ifndef  DAYNAMIC_ARRAY
#define DAYNAMIC_ARRAY

typedef struct {
    char *date;
    char *message;
}History ;

typedef struct HistoryArray {
    History **history;    
    int length;
    void (*add_text) (struct HistoryArray *str_arr, char *date, char *message);
} HistoryArray ;

void add_text(HistoryArray *history_arr, char *date, char *message);
#endif