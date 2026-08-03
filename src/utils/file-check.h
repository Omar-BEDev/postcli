#ifndef CHECK_FILE
#define CHECK_FILE

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if a file is available
 * @param file_name The name of the file to check
 * @return 1 if available, 0 or -1 if not
 */
int is_file_available(const char *file_name);

#ifdef __cplusplus
}
#endif
#endif