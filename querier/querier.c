/*
 * querier.c 
 *
 * This module implements a search engine querier that reads an index file and a directory of web page files, processes user queries, and returns a ranked list of documents that match the queries.
 * 
 * Firdavskhon Babaev
 */

#include <stdio.h>
#include "index.h"
#include <dirent.h>
#include "mem.h"
#include "file.h"
#include "word.h"
#include <string.h>
#include "pagedir.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h> 

#define MAX_QUERY 1000
#define MAX_TOKENS 100
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Function prototypes
static void display_prompt();
static void parseArgs(int argc, char* argv[], char** pageDirectory, char** indexFilename);
int tokenize_query(char* query, char* words[]);
bool validate_user_query(char* words[], int numTokens);
void* perform_lookup(index_t* index, char* words[], int numTokens);
void find_max_score(void* arg, int docID, int score);
static void merge_counters(counters_t* ctrA, counters_t* ctrB);
static void merge_counters_helper(void* arg, int key, int item);
static void intersect_counters(counters_t* ctrA, counters_t* ctrB);
static void intersect_counters_helper(void* arg, int key, int item);
static void rank_search_results(counters_t* result, char* pageDirectory);
static void count_items(void* arg, int key, int count);

int main(int argc, char *argv[]) {
    char* pageDirectory;
    char* indexFilename;
    char* query = mem_malloc(MAX_QUERY); // Allocate memory for the query
    int numTokens;
    counters_t* answer;
    char* words[MAX_QUERY];

    // Parse command-line arguments
    parseArgs(argc, argv, &pageDirectory, &indexFilename);

    // Load the index file
    FILE* input = fopen(indexFilename, "r");
    index_t* index = index_load(input);
    fclose(input);

    // Display the prompt for user input
    display_prompt();
    
    // Read queries from stdin until EOF
    if (fgets(query, MAX_QUERY, stdin) != NULL) {
        while (query != NULL && *query != '\0') {
            // Tokenize the query into words
            numTokens = tokenize_query(query, words);
            
            if (numTokens > 0) {
                // Validate the user query for logical correctness
                if (validate_user_query(words, numTokens)) {
                    // Display the cleaned and validated query
                    printf("Query:");
                    for (int i = 0; i < numTokens; i++) {
                        printf(" %s", words[i]);
                    }
                    printf("\n");

                    // Perform the query lookup in the index and rank the results
                    answer = perform_lookup(index, words, numTokens);
                    rank_search_results(answer, pageDirectory);

                    // Clean up the result set
                    counters_delete(answer);
                }
            }

            // Prompt for the next query
            display_prompt();
            
            // Get the next query from stdin
            if (fgets(query, MAX_QUERY, stdin) == NULL) {
                break;
            }
        }
    }

    // Free the allocated memory and delete the index structure
    free(query);
    index_delete(index);
}

// Function to parse and validate command-line arguments
static void parseArgs(int argc, char* argv[], char** pageDirectory, char** indexFilename) {
    if (argc == 3) {
        *pageDirectory = argv[1];
        *indexFilename = argv[2];

        // Verify the pageDirectory exists and is a valid directory
        DIR* dir = opendir(*pageDirectory);
        if (dir != NULL) {
            if (!pagedir_validate(*pageDirectory)) {
                fprintf(stderr, "Error: %s is not a crawler-produced directory \n", *pageDirectory);
                exit(2);
            }
            mem_free(dir);
        } else {
            fprintf(stderr, "Error: %s does not exist \n", *pageDirectory);
            mem_free(dir);
            exit(2);
        }

        // Verify the indexFilename can be opened and read
        FILE* indexFile = fopen(*indexFilename, "r");
        if (indexFile != NULL) {
            fclose(indexFile);
        } else {
            fprintf(stderr, "Error: cannot read %s \n", *indexFilename);
            exit(2);
        }
    } else {
        fprintf(stderr, "usage: ./%s pageDirectory indexFilename \n", argv[0]);
        exit(1);
    }
}

// Function to tokenize the query string into individual words
int tokenize_query(char* query, char* words[]) {
    int numTokens = 0;
    char* word = query;
    char* rest = query;

    while (*word != '\0') {
        // Check for invalid characters in the query
        if (!(isalpha(*word)) && !(isspace(*word))) {
            fprintf(stderr, "Error: bad character '%c' in query \n", *word);
            return -1;
        }

        // Process each word in the query
        if (isalpha(*word)) {
            rest = word;
            while (isalpha(*rest)) {
                rest++;
            }
            if (!(isspace(*rest))) {
                fprintf(stderr, "Error: bad character '%c' in query \n", *rest);
                return -1;
            }
            *rest = '\0';
            numTokens++;
            normalizeWord(word);
            words[numTokens-1] = word;
            word = rest + 1;
        } else {
            word++;
            if (*word == '\0') {
                return numTokens;
            }
        }
    }
    return numTokens;
}

// Function to validate the user query based on specific rules
bool validate_user_query(char* words[], int numTokens) {
    if (strcmp(words[0], "or") == 0 || strcmp(words[0], "and") == 0) {
        fprintf(stderr, "Error: '%s' cannot be first \n", words[0]);
        return false;
    }
    if (strcmp(words[numTokens-1], "or") == 0 || strcmp(words[numTokens-1], "and") == 0) {
        fprintf(stderr, "Error: '%s' cannot be last \n", words[numTokens-1]);
        return false;
    }
    for (int i = 0; i < numTokens - 1; i++) {
        if ((strcmp(words[i], "or") == 0 && strcmp(words[i + 1], "or") == 0) || 
            (strcmp(words[i], "or") == 0 && strcmp(words[i + 1], "and") == 0) || 
            (strcmp(words[i], "and") == 0 && strcmp(words[i + 1], "or") == 0) || 
            (strcmp(words[i], "and") == 0 && strcmp(words[i + 1], "and") == 0)) {
            fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent \n", words[i], words[i + 1]);
            return false;
        }
    }
    return true;
}

// Function to perform the lookup in the index and retrieve results
void* perform_lookup(index_t* index, char* words[], int numTokens) {
    counters_t* result = counters_new();
    counters_t* temp = hashtable_find(index, words[0]);

    for (int i = 1; i <= numTokens; i++) {
        if (i == numTokens) {
            merge_counters(result, temp);
            return result;
        } else if (strcmp(words[i], "and") == 0) {
            continue;
        } else if (strcmp(words[i], "or") == 0) {
            merge_counters(result, temp);
            temp = hashtable_find(index, words[i + 1]);
        } else {
            counters_t* curr = hashtable_find(index, words[i]);
            intersect_counters(temp, curr);
        }
    }
    return result;
}

// Function to rank and display the search results
static void rank_search_results(counters_t* result, char* pageDirectory) {
    int numItems = 0;
    counters_iterate(result, &numItems, count_items);
    if (numItems == 0) {
        printf("No documents match. \n");
        return;
    }

    int maxScore;
    int maxID;

    do {
        maxScore = 0;
        maxID = 0;
        int maxDoc[] = {maxID, maxScore};
        counters_iterate(result, maxDoc, find_max_score);
        maxID = maxDoc[0];
        maxScore = maxDoc[1];
        if (maxScore > 0) {
            char docname[256];
            snprintf(docname, sizeof(docname), "%s/%d", pageDirectory, maxID);
            char* url;
            FILE* fp = fopen(docname, "r");
            if (fp != NULL) {
                url = file_readLine(fp);
                fclose(fp);
            }
            printf("score %d doc %d: %s\n", maxScore, maxID, url);
            free(url);
            counters_set(result, maxID, 0);
            maxDoc[0] = 0;
            maxDoc[1] = 0;
        }

    } while (maxScore > 0);
}

// Function to count the number of non-zero items in the counter set
static void count_items(void* arg, int key, int count) {
    int* nitems = arg;
    if (count != 0) {
        (*nitems)++;
    }
}

// Function to intersect two counter sets
static void intersect_counters(counters_t* ctrA, counters_t* ctrB) {
    struct twosets { counters_t *ctr1, *ctr2; };
    struct twosets ctrs = {ctrA, ctrB};
    counters_iterate(ctrA, &ctrs, intersect_counters_helper);
}

// Helper function for intersecting counters
static void intersect_counters_helper(void* arg, int key, int item) {
    struct twosets { counters_t *ctr1, *ctr2; };
    struct twosets* ctrs = arg;
    counters_t* ctrA = ctrs->ctr1;
    counters_t* ctrB = ctrs->ctr2;

    int countB = counters_get(ctrB, key);
    int countA = item;
    if (countB == 0) {
        counters_set(ctrA, key, 0);
    } else {
        counters_set(ctrA, key, MIN(countA, countB));
    }
}

// Function to merge two counter sets
static void merge_counters(counters_t* ctrA, counters_t* ctrB) {
    counters_iterate(ctrB, ctrA, merge_counters_helper);
}

// Helper function for merging counters
static void merge_counters_helper(void* arg, int key, int item) {
    counters_t* ctrA = arg;
    int docID = key;
    int countB = item;
    int countA = counters_get(ctrA, docID);
    counters_set(ctrA, docID, countA + countB);
}

// Function to find the document with the maximum score
void find_max_score(void* arg, int docID, int score) {
    int* maxDoc = arg;
    int maxScore = maxDoc[1];
    if (score >= maxScore) {
        maxDoc[0] = docID;
        maxDoc[1] = score;
    }
}

int fileno(FILE *stream);

// Function to display a prompt if stdin is a terminal
static void display_prompt(void) {
    if (isatty(fileno(stdin))) {
        printf("Query? ");
    }
}
