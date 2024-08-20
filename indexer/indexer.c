/*
 * indexer.c - CS50 'indexer' module
 *
 * The indexer scans through web pages previously stored by the crawler, constructs an index mapping words to document IDs and occurrence counts, and outputs this index to a specified file.
 *
 * Author: Firdavskhon Babaev
 * Date: May 6, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"
#include "webpage.h"
#include "pagedir.h"
#include "index.h"
#include "word.h"

void indexPage(webpage_t *page, int docID, index_t *index);
bool pagedir_validate(const char *pageDirectory);
webpage_t *pagedir_load(const char *pageDirectory, int docID);
index_t *indexBuild(const char *pageDirectory);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./indexer pageDirectory indexFilename\n");
        return 1;
    }

    char *pageDirectory = argv[1];
    char *indexFilename = argv[2];

    if (!pagedir_validate(pageDirectory)) {
        fprintf(stderr, "Error: The specified page directory is invalid\n");
        return 1;
    }

    index_t *index = indexBuild(pageDirectory);
    if (index == NULL) {
        fprintf(stderr, "Error: Unable to construct index from page directory\n");
        return 1;
    }

    FILE *fp = fopen(indexFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open index file for writing\n");
        index_delete(index);
        return 1;
    }

    if (index_save(fp, index)) {
        fprintf(stderr, "Error: Index could not be saved to file\n");
        fclose(fp);
        index_delete(index);
        return 1;
    }

    fclose(fp);
    index_delete(index);
    return 0;
}

void indexPage(webpage_t *page, int docID, index_t *index) {
    int pos = 0;
    char *html = webpage_getHTML(page);
    if (html == NULL) {
        return;
    }

    // Move past the first two lines of HTML
    int newlineCount = 0;
    while (newlineCount < 2 && html[pos] != '\0') {
        if (html[pos] == '\n') {
            newlineCount++;
        }
        pos++;
    }

    char* word;

    while ((word = webpage_getNextWord(page, &pos)) != NULL) {
        if (strlen(word) >= 3) {
            normalizeWord(word);
            counters_t *counters = hashtable_find(index, word);
            if (counters == NULL) {
                counters = counters_new();
                if (counters != NULL) {
                    hashtable_insert(index, word, counters);
                }
            }
            if (counters != NULL) {
                counters_add(counters, docID);
            }
        }
        free(word);
    }
}

index_t *indexBuild(const char *pageDirectory) {
    index_t *index = index_new(100);
    if (index == NULL) {
        return NULL;
    }

    int docID = 1;
    webpage_t *page;
    while ((page = pagedir_load(pageDirectory, docID)) != NULL) {
        indexPage(page, docID, index);
        webpage_delete(page);
        docID++;
    }

    return index;
}
