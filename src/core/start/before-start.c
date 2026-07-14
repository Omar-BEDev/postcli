#include "../../io/logs/logs.h"
#include "../../utils/file-check.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Makes a log file if it does not exist
 * @param log_file_name The name of the log file
 */
void make_log_file(char *log_file_name) {
  if (is_file_available(log_file_name) == -1) {
    log_path_generate(LINUX_HOME_DIR);
  } else {
    return;
  }
}

/**
 * @brief Shows the program logo
 */
void show_program_logo() {
    FILE *logo_file = fopen("src/utils/logo.txt","r");
    if (logo_file == NULL) {
        printf("error: logo not found");
        return;
    }
    char buf[256];
    while(fgets(buf,sizeof(buf),logo_file) != NULL) {
        printf("%s",buf);
    }
    fclose(logo_file);
}