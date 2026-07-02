#include "dynamic-array.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add_history_elements(
    HistoryArray *history_arr, char *date, int date_length,
    char *message, int message_length
) {
    int i = 0;
    while (i < date_length) {
        history_arr->history[history_arr->length - 1]->date[i] = date[i];
        i++;
    }
    history_arr->history[history_arr->length - 1]->date[i] = '\0';

    i = 0;
    while (i < message_length) {
        history_arr->history[history_arr->length - 1]->message[i] = message[i];
        i++;
    }

    history_arr->history[history_arr->length - 1]->message[i] = '\0';
}

void add_text(HistoryArray *history_arr, char *date, char *message) {
    if (history_arr == NULL) {
        printf("history not found");
        return;
    }
    history_arr->length++;
    history_arr->history = realloc(history_arr->history, history_arr->length * sizeof(History*));
    history_arr->history[history_arr->length - 1] = malloc(sizeof(History));
    int date_length = strlen(date);
    int message_length = strlen(message);
    history_arr->history[history_arr->length - 1]->date = malloc(date_length * sizeof(char) + 1);
    history_arr->history[history_arr->length - 1]->message = malloc(message_length * sizeof(char) + 1);
    add_history_elements(history_arr, date, date_length, message, message_length);
    
}

