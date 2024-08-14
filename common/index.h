/*
 * index.h - common directory
 *
 * This header file defines the interface for the 'index' module, which provides functions to create, modify, save, and load an index that maps words to document IDs and their counts. This index is crucial for the 'indexer' and 'querier' modules, enabling efficient searching across crawled webpages.
 *
 * Author: Firdavskhon Babaev
 * Date: May 5, 2024
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include "file.h"
#include "hashtable.h"
#include "counters.h"

// Define the index type as a hashtable
typedef hashtable_t index_t;

/* 
 * Create a new index with a specified number of slots.
 * Returns a pointer to the newly created index.
 */
index_t* index_new(const int num_slots);

/* 
 * Add a word with its associated document ID to the index.
 * If the word already exists, it updates the document ID count.
 */
void index_add(index_t *index, const char *word, int docID);

/* 
 * Delete the entire index, freeing all associated memory.
 */
void index_delete(index_t* index);

/* 
 * Save the current state of the index to a file.
 * Returns 0 on success, and 1 on failure (e.g., if the file pointer is NULL).
 */
int index_save(FILE* fp, index_t* index);

/* 
 * Load an index from a file, reconstructing it from the file's data.
 * Returns a pointer to the newly loaded index.
 */
index_t* index_load(FILE* fp);

#endif // __INDEX_H
