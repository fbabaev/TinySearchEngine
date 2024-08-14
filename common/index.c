/*
 * index.c - CS50 'common' directory
 *
 * This module implements an index data structure that maps words to document IDs and their corresponding occurrence counts. The index is essential for efficient search operations in the 'indexer' and 'querier' modules, facilitating quick lookups of words across crawled webpages.
 *
 * Author: Firdavskhon Babaev
 * Date: May 5, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "hashtable.h"
#include "counters.h"

// Define the index type as a hashtable
typedef hashtable_t index_t;

// Create a new index with a specified number of slots
index_t* index_new(const int num_slots) {
    return hashtable_new(num_slots);
}

// Add a document ID to the index under the given word
void index_add(index_t *index, const char *word, int docID) {
    counters_t *counters = hashtable_find(index, word);
    if (counters == NULL) {
        counters = counters_new();
        hashtable_insert(index, word, counters);
    }
    counters_add(counters, docID);
}

// Helper function to delete a counters data structure
void counters_delete_fn(void *item) {
    counters_t *counters = item;
    counters_delete(counters);
}

// Delete the entire index, freeing all associated memory
void index_delete(index_t* index) {
    hashtable_delete(index, counters_delete_fn);
}

// Save a single item in the counters data structure to a file
void counters_item_save(void* arg, const int key, const int item) {
    FILE* fp = arg;
    fprintf(fp, "%d %d ", key, item);
}

// Save a single item in the index to a file
void index_item_save(void* arg, const char* key, void* item) {
    FILE* fp = arg;
    counters_t* counters = item;

    fprintf(fp, "%s ", key);
    counters_iterate(counters, fp, counters_item_save);
    fprintf(fp, "\n");
}

// Save the entire index to a file
int index_save(FILE* fp, index_t* index) {
    if (fp == NULL || index == NULL) {
        return 1; 
    }
    hashtable_iterate(index, fp, index_item_save);
    return 0;
}

// Load an index from a file, reconstructing it from the file's data
index_t* index_load(FILE* fp) {
    int size = file_numLines(fp);
    index_t* newIndex = index_new(size);
    char* word;

    // Read words and their associated document ID counts from the file
    while ((word = file_readWord(fp)) != NULL) {
        counters_t* ctr = counters_new();
        int docID, count;

        // Read and set (docID, count) pairs in the counters
        while (fscanf(fp, "%d %d", &docID, &count) == 2) {
            counters_set(ctr, docID, count);
        }
        hashtable_insert(newIndex, word, ctr);
        free(word);
    }
    return newIndex;
}
