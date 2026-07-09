#include <sys/stat.h>
int is_file_available(const char *file_name) {
    struct stat buf;
    if(stat(file_name, &buf) == 0) {
        return S_ISREG(buf.st_mode);
    }
    return 0;
}