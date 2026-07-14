#include <sys/stat.h>
/**
 * @brief Checks if a file is available
 * @param file_name The name of the file to check
 * @return 1 if available, 0 or -1 if not
 */
int is_file_available(const char *file_name) {
    struct stat buf;
    if(stat(file_name, &buf) == 0) {
        return S_ISREG(buf.st_mode);
    }
    return -1;
}