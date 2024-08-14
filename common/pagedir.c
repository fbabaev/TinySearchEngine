/*
 * pagedir.c -'pagedir' module
 *
 * This module provides functions to manage a directory of webpages, which are saved to and loaded from the filesystem. The module includes functions to initialize a directory, save webpages, validate the directory, and load webpages based on document IDs.
 *
 * Author: Firdavskhon Babaev
 * Date: April 29, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "pagedir.h"
#include "file.h"

/*
 * Initializes the page directory by creating a ".crawler" file within the directory.
 * This file serves as an indicator that the directory was created by the crawler.
 * Returns true if the file was successfully created, false otherwise.
 */
bool pagedir_init(const char* pageDirectory) {
    char crawlerFilePath[256];
    snprintf(crawlerFilePath, sizeof(crawlerFilePath), "%s/.crawler", pageDirectory);
    FILE *fp = fopen(crawlerFilePath, "w");
    if (fp != NULL) {
        fclose(fp);
        return true;
    } else {
        return false;
    }
}

/*
 * Saves a webpage to a file in the specified page directory.
 * The file is named according to the document ID, and it contains the URL, depth, and HTML content of the webpage.
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {
    char pageFilePath[256];
    snprintf(pageFilePath, sizeof(pageFilePath), "%s/%d", pageDirectory, docID);
    FILE *fp = fopen(pageFilePath, "w");
    if (fp != NULL) {
        fprintf(fp, "%s\n%d\n%s\n", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
        fclose(fp);
    }
}

/*
 * Validates the page directory by checking for the presence of the ".crawler" file.
 * Returns true if the file exists, indicating that the directory was created by the crawler, false otherwise.
 */
bool pagedir_validate(const char* pageDirectory) {
    char crawlerFilePath[256];
    snprintf(crawlerFilePath, sizeof(crawlerFilePath), "%s/.crawler", pageDirectory);
    FILE *fp = fopen(crawlerFilePath, "r");
    if (fp != NULL) {
        fclose(fp);
        return true;
    } else {
        return false;
    }
}

/*
 * Loads a webpage from a file in the specified page directory using the document ID.
 * The function reads the URL and HTML content from the file and creates a new webpage object.
 * Returns a pointer to the newly created webpage, or NULL if the file could not be opened or an error occurred.
 */
webpage_t* pagedir_load(const char* pageDirectory, const int docID) {
    char pageFilePath[256];
    snprintf(pageFilePath, sizeof(pageFilePath), "%s/%d", pageDirectory, docID);
    FILE *fp = fopen(pageFilePath, "r");
    if (fp != NULL) {
        char *url = malloc(256);
        if (url == NULL) {
            // If malloc failed, close the file and return NULL
            fclose(fp);
            free(url);
            return NULL;
        }
        
        webpage_t *page = webpage_new(url, 0, file_readFile(fp));
        fclose(fp);
        return page;
    } else {
        return NULL;
    }
}

