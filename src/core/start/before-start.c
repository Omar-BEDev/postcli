#include "../../io/logs/logs.h"
#include "../../utils/file-check.h"
#include <stdio.h>
#include <stdlib.h>

void make_log_file(char *log_file_name) {
  if (is_file_available(log_file_name) == -1) {
    log_path_generate(LINUX_HOME_DIR);
  } else {
    return;
  }
}

void show_program_logo() {
    FILE *logo_file = fopen("logo.txt","r");
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