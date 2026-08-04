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
    void (*remove_history_log) (char *file_name);
} HistoryArray ;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Adds a history log to the array
 * @param history_arr The history array
 * @param date The date of the log
 * @param message The log message
 */
void add_history_log(HistoryArray *history_arr, char *date, char *message);
/**
 * @brief Removes the content of the history log file
 * @param file_name The name of the file to remove
 */
void remove_history_log(char *file_name);
/**
 * @brief Initializes a history array struct
 * @param history_arr The history array to initialize
 */
void initialize_history_array(HistoryArray *history_arr);
/**
 * @brief Frees all memory allocated for the history array
 * @param history_arr The history array to free
 */
void free_history_array(HistoryArray *history_arr);

#ifdef __cplusplus
}
#endif
#endif
