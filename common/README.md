# Common Directory README

## Introduction
The Common directory is an integral part of the Tiny Search Engine (TSE) that houses shared utilities and modules used across multiple components of the project. This README outlines the contents and functionalities of each module within the Common directory, facilitating effective integration and usage across the TSE components.

## Modules

### 1. Index Module
**Description**: The Index module is central to the TSE, providing robust mechanisms for creating, manipulating, saving, and loading an index. The index is an inverted data structure that maps words to their occurrences in documents (document IDs and counts).

**Functionality**:
- **Create Index**: Initializes an empty index.
- **Add to Index**: Updates the index with word-document ID pairs and their occurrence counts.
- **Save Index**: Writes the index to a file in a format that can be easily loaded later.
- **Load Index**: Reads an index from a file and reconstructs the index data structure.

**Used by**: This module is utilized by both the Indexer to build the index and the Querier to retrieve indexed data for processing queries.

### 2. Pagedir Module
**Description**: The Pagedir module manages the directories where crawled web pages are stored. It includes functions for initializing, saving, validating, and loading these directories to ensure data integrity and proper access throughout the engine's operation.

**Functionality**:
- **Initialize Directory**: Prepares a directory to store crawled web pages.
- **Save Page**: Stores a web page file in the designated directory.
- **Validate Directory**: Checks if a directory contains valid crawler output.
- **Load Page**: Retrieves a page from the directory for processing.

**Used by**: Essential for the Crawler to store pages and the Querier to access the stored pages.

### 3. Word Module
**Description**: The Word module handles the normalization of words, which is critical for the indexing and query processing phases of the TSE.

**Functionality**:
- **Normalize Word**: Converts a word to lowercase to standardize the index and search processes. This ensures that searches are case-insensitive and consistent across various text inputs.

**Used by**: It is used in the Indexer to process words before adding them to the index, and in the Querier when parsing and processing user queries.

## Usage
Modules in the Common directory are implemented as libraries and are linked to other components of the TSE during compilation. Each module comes with its own header (.h) and implementation (.c) files, which should be included and linked appropriately in the makefiles of other components.

