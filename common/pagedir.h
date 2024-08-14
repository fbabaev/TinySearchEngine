/*
 * pagedir.h -'pagedir' module
 *
 * This header file provides the interface for managing a directory of webpages. The functions declared here allow for initializing the directory, saving webpages, validating the directory, and loading webpages by document ID.
 *
 * Firdavskhon Babaev
 * Date: April 29, 2024
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdbool.h>
#include "webpage.h"
#include "file.h"

/* 
 * Initialize a page directory by creating a ".crawler" file within the directory.
 * This function returns true if the directory was successfully initialized, otherwise false.
 */
bool pagedir_init(const char* pageDirectory);

/* 
 * Save a webpage to a file in the specified page directory.
 * The file is named based on the document ID and contains the URL, depth, and HTML content of the webpage.
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/* 
 * Validate the page directory by checking for the existence of the ".crawler" file.
 * Returns true if the directory is valid, otherwise false.
 */
bool pagedir_validate(const char* pageDirectory);

/* 
 * Load a webpage from a file in the specified page directory using the document ID.
 * Returns a pointer to the newly created webpage, or NULL if loading fails.
 */
webpage_t* pagedir_load(const char* pageDirectory, const int docID);

#endif // __PAGEDIR_H
