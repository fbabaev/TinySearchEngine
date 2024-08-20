### TSE Indexer
#### Implementation Specification

This document builds upon the Design Specification by detailing implementation-specific decisions for the CS50 TSE Indexer project. Our focus is on essential components such as data structures, control flow, function prototypes, error handling, and testing.

#### Data Structures
The primary data structure is an **index**, implemented as a hashtable. Each key in the hashtable is a word, and each value is a counterset that maps document IDs to the counts of occurrences.

#### Control Flow
**Main Functions Overview:**

- `main`: Parses command-line arguments, initializes modules, and invokes `indexBuild` with the `pageDirectory` as an argument.

- `indexBuild`: Constructs a new index object and iterates over document IDs, loading webpages and processing them through `indexPage`.

- `indexPage`: Processes each word in the webpage, normalizing it and updating the index with the word count per document.

#### Function Prototypes
- `int main(const int argc, char* argv[]);`
- `void indexBuild(char* pageDirectory);`
- `void indexPage(webpage_t *page, const int docID, index_t *index);`

#### Error Handling and Recovery
- **Command-line errors:** Rigorous checks ensure early termination with appropriate error messages if parameters are invalid.
  
- **Memory allocation errors:** Out-of-memory conditions trigger assertions that print errors to `stderr` and exit with a non-zero status.

- **Defensive programming:** All functions are designed to handle incorrect inputs gracefully, verifying parameters before proceeding.

#### Testing Plan
**Unit Testing:**
- `indextest` acts as a unit test for the index module, reading from and writing to index files to test the integrity of data structures.

**Integration Testing:**
- Comprehensive testing of `indexer` using a variety of `pageDirectory` inputs to ensure correct index creation.
- Validation via `indextest` to confirm that indexes are correctly formatted and readable.
- Specific test scenarios include:
  1. Missing or excessive command-line arguments.
  2. Non-existent or incorrect `pageDirectory`.
  3. Inaccessible or invalid `indexFile` scenarios.
  4. Memory and error checks using Valgrind to confirm the absence of leaks or runtime errors.

The outlined approach ensures thorough validation at both unit and integration levels, maintaining high standards for code quality and functionality.
