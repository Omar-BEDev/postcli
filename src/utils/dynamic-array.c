#include "dynamic-array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/**
 * @brief Adds a history log to the array
 * @param history_arr The history array
 * @param date The date of the log
 * @param message The log message
 */
void add_history_log(HistoryArray *history_arr, char *date, char *message) {
    if (history_arr == NULL) {
        printf("error : history not found");
        return;
    }
    history_arr->length++;
    history_arr->history = realloc(history_arr->history, history_arr->length * sizeof(History*));
    history_arr->history[history_arr->length - 1] = malloc(sizeof(History));
    int date_length = strlen(date);
    int message_length = strlen(message);
    history_arr->history[history_arr->length - 1]->date = malloc(date_length * sizeof(char) + 1);
    history_arr->history[history_arr->length - 1]->message = malloc(message_length * sizeof(char) + 1);
    strcpy(history_arr->history[history_arr->length - 1]->date,date);
    strcpy(history_arr->history[history_arr->length - 1]->message,message);
}

/**
 * @brief Removes the history log file
 * @param file_name The name of the file to remove
 */
void remove_history_log(char* file_name) {
    FILE *log_file = fopen(file_name, "w");
    if (log_file == NULL) {
        printf("error : delete log file content failed");
        return;
    }
    fclose(log_file);
}