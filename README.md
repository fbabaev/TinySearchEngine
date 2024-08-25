# Tiny Search Engine

## Overview

The Tiny Search Engine (TSE) is a comprehensive software project. This document provides an extensive overview of the TSE, detailing its architecture, components, and usage. The engine is divided into three main components: Crawler, Indexer, and Querier.

## Components

### 1. Crawler
The Crawler is the first component of the TSE. It systematically downloads web pages starting from a seed URL and explores further by following hyperlinks to a specified depth. This component is crucial for gathering the raw data on which the search engine operates.

**Key Features:**
- Depth-limited crawling to control the scope of data collection.
- Detection and avoidance of revisiting the same URL.
- Storage of crawled pages in a specified directory with a unique document ID for each page.

**Usage:**
To run the Crawler:
```bash
./crawler seedURL pageDirectory maxDepth
```
* `seedURL`: The starting URL for the crawler.
* `pageDirectory`: Directory to store downloaded pages.
* `maxDepth`: Maximum link depth to explore.

### 2. Indexer
The Indexer constructs an inverted index from the pages stored by the Crawler. This index maps each unique word found in the pages to the document IDs where the word appears, along with the frequency of occurrences in each document.

**Key Features:**
- Efficient data structure for quick lookup of words.
- Handles normalization of words (e.g., converting to lowercase) to ensure consistency.
- Outputs the index to a file for use by the Querier.

**Usage:**
To run the Indexer:
```bash
./indexer pageDirectory indexFilename
```
* `pageDirectory`: Directory containing the .crawler files.
* `indexFilename`: Filename to write the inverted index.

### 3. Querier
The Querier uses the inverted index generated by the Indexer to answer search queries. It supports complex queries involving logical 'AND' and 'OR' operators.

**Key Features:**
- Interpretation of complex queries with logical operators.
- Ranking of search results based on the frequency and distribution of query terms across documents.
- Outputs a list of documents that best match the query terms.

**Usage:**
To run the Querier:
```bash
./querier pageDirectory indexFilename
```
* `pageDirectory`: Directory containing the .crawler files.
* `indexFilename`: Filename containing the inverted index.

## Building and Testing

To build the entire project:
```bash
make
```

To run predefined tests for all components:
```bash
make test
```

To clean up the project directory:
```bash
make clean
```

## Additional Information

Each component of the TSE is contained within its own directory, complete with specific README files that provide more detailed instructions and implementation details. Users are encouraged to refer to these files to understand the operational intricacies of each component.

The `pageDirectory` folder is integral for the operation of the TSE, serving as the repository for storing `.crawler` files and the subsequent indexing and querying operations.
