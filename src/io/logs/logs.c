#include "logs.h"
#include "../../utils/dynamic-array.h"
#include <stdio.h>


void read_file_logs(HistoryArray *history_arr, FILE *log_file) {
    char buf[1024];
    char date[11];
    char message[50];
    int i = 0;
    int message_index = 0;

    while (fgets(buf, sizeof(buf), log_file) != NULL) {
    while (buf[i] != '\n' && buf[i] != '\0') {

      if (i < DATE_LENGTH) {
        date[i] = buf[i];
      }
      if (i >= FIRST_MESSAGE_INDERX_POSITION && message_index <= 48) {
        message[message_index] = buf[i];
        message_index++;
      }
      i++;
    }
    date[DATE_LENGTH] = '\0';
    message[message_index] = '\0';
    history_arr->add_history_log(history_arr, date, message);
    i = 0;
    message_index = 0;
  }
}

void extract_logs(HistoryArray *history_arr, char *path) {
  FILE *log_file = fopen(path, "r");
  if (log_file == NULL) {
    printf("error: file not found");
    return;
  }
  read_file_logs(history_arr, log_file); 
  fclose(log_file);
}

