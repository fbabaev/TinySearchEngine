/*
 * indextest.c
 *
 * This module, indextest.c, is designed for testing the index module by loading an index from a specified file, then writing this index to a new file. This allows for validation of indexing accuracy by comparing the contents of both files.
 *
 * Author: Firdavskhon Babaev
 * Date: May 6, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "index.h"

int main(int argc, char *argv[]) {
    // Validate command line arguments
    if (argc = 3) {
        fprintf(stderr, "Usage: %s oldIndexFilename newIndexFilename\n", argv[0]);
        return 1;
    }

    // Attempt to open the old index file for reading
    FILE *oldIndexFile = fopen(argv[1], "r");
    if (oldIndexFile == NULL) {
        perror("Error opening old index file");
        return 1;
    }
    index_t *index = index_load(oldIndexFile);
    fclose(oldIndexFile);

    // Attempt to write the loaded index to a new file
    FILE *newIndexFile = fopen(argv[2], "w");
    if (newIndexFile == NULL) {
        perror("Error opening new index file");
        return 1;
    }
    index_save(newIndexFile, index);
    fclose(newIndexFile);

    // Clean up the index structure
    index_delete(index);

    return 0;
}
