# CS50 TSE Indexer

## Overview

The TSE Indexer is a specialized component of the Tiny Search Engine (TSE), engineered to process web pages archived by the TSE Crawler. It systematically generates a searchable index that maps words to document IDs and the frequency of those words within each document. This index is pivotal for facilitating efficient query processing in the larger TSE suite.

## Features

- **Efficient Indexing:** Quickly parses and indexes content from numerous web pages, creating a manageable data structure that maps each word to its document location and occurrence count.
- **Scalability:** Designed to efficiently handle large volumes of data, the indexer scales seamlessly with the size of the input, maintaining performance even as data grows.
- **Error Handling:** Implements comprehensive error checking and recovery protocols to manage exceptions and ensure consistent operation under varied conditions.
- **Memory Management:** Utilizes rigorous memory management practices to ensure that all resources are appropriately allocated and freed, preventing leaks and maximizing efficiency.

## Components

- **indexer.c**: The main executable that orchestrates the indexing process. It reads web pages from a directory, processes each page, and compiles a comprehensive index.
- **indextest.c**: A utility to validate and test the integrity of the index file. It loads an index file, verifies its structure, and optionally re-outputs the index for comparison.
- **data structures**: Utilizes a combination of hash tables and counter sets to efficiently store and access the indexing data.

## Algorithm Overview

### Data Structures
- **Hashtable:** Used to map words to their corresponding `counters` structure.
- **Counters:** A set of counters for each word, where each counter corresponds to a document ID and the count of the word's occurrences in that document.

### Process Flow
1. **Initialization:** Sets up the hashtable and prepares for processing.
2. **Web Page Loading:** Sequentially loads web pages stored by the crawler.
3. **Word Processing:**
   - Extracts words from each page.
   - Normalizes words to lowercase to ensure consistency.
   - Skips non-substantive words (e.g., words shorter than three characters).
4. **Index Updating:**
   - For each word, checks if it is already in the hashtable.
   - If new, initializes a counter set for that word.
   - Updates the counter for the corresponding document ID.
5. **Output:** Once all pages are processed, the index is written to a file in a format that maps each word to its document IDs and counts.

### Testing Plan

**Unit Testing:**
- Uses `indextest` to read and write the index, ensuring data integrity and consistency.

**Integration Testing:**
- Tests the indexer with various data volumes and formats to ensure it behaves as expected across different scenarios and edge cases.

**Memory and Error Handling:**
- Employs Valgrind and similar tools to ensure there are no memory leaks or errors during execution.

