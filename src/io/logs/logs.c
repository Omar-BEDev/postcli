#include "logs.h"
#include "../../utils/dynamic-array.h"
#include <stdio.h>

/**
 * @brief Creates the log file directory path
 * @param program_path The output path
 * @param dir The base directory
 * @param program_folder_name The folder name
 * @param log_file_name The log file name
 */
void make_log_dir(char *program_path, char *dir,
                       char *program_folder_name, char *log_file_name) {
  strcpy(program_path, dir);
  strcat(program_path, "/");
  strcat(program_path, program_folder_name);
  strcat(program_path, "/");
  strcat(program_path, log_file_name);
}

/**
 * @brief Creates the log folder directory path
 * @param folder_path The output path
 * @param dir The base directory
 * @param program_folder_name The folder name
 */
void make_log_folder_dir(char *folder_path,char *dir, char *program_folder_name) {
    strcpy(folder_path, dir);
    strcat(folder_path, "/");
    strcat(folder_path, program_folder_name);
}


/**
 * @brief Generates the path for the log directory
 * @param dir The directory path
 */
void log_path_generate(char *dir) {
  char program_path[512];
  char folder_path[256];
  char *program_folder_name = "postcli-tool";
  char *log_file_name = "logs.log";
  make_log_dir(program_path, dir, program_folder_name, log_file_name);
  make_log_folder_dir(folder_path, dir, program_folder_name);
  if (make_folder(folder_path) == 0) {
    FILE *log_file = fopen(program_path, "w");
    if (log_file == NULL) {
      printf("error: log not found");
      return;
    }
    fclose(log_file);
  }
}

/**
 * @brief Reads logs from a file and stores them
 * @param history_arr The history array to populate
 * @param log_file The file pointer to read from
 */
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

/**
 * @brief Extracts logs from a given path
 * @param history_arr The history array to extract to
 * @param path The path of the log file
 */
void extract_logs(HistoryArray *history_arr, char *path) {
  FILE *log_file = fopen(path, "r");
  if (log_file == NULL) {
    printf("error: file not found");
    return;
  }
  read_file_logs(history_arr, log_file);
  fclose(log_file);
}
