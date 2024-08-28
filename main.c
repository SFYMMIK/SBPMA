#include "src/include/gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    // File list and count
    extern char *file_list[];
    extern int file_count;

    for (int i = 1; i < argc && i < MAX_FILES; i++) {
        file_list[i - 1] = strdup(argv[i]);
        file_count++;
    }

    create_gui();

    return 0;
}
