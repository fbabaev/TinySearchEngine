# Querier Implementation Specification

## Overview

The querier component of the Tiny Search Engine (TSE) is designed to process and respond to user queries by identifying relevant documents from a set of indexed web pages. This specification outlines the detailed implementation approach for the querier, including its primary functions and responsibilities.

## Main Function

### `main()`
- **Description**: Serves as the entry point for the querier program.
- **Responsibilities**:
  - Handle the parsing of command-line arguments.
  - Initialize the index from the specified file.
  - Continuously process queries entered by the user.
  - Manage resource cleanup prior to program termination.

## Argument Handling

### `parseArgs()`
- **Description**: Validates and parses the command-line arguments provided to the querier.
- **Responsibilities**:
  - Check that exactly two arguments (pageDirectory and indexFilename) are provided.
  - Confirm the existence and format of the page directory.
  - Verify accessibility and format of the index file.
  - Assign global variables to the paths provided.

## Query Processing

### `display_prompt()`
- **Description**: Displays a user prompt for input in interactive mode.
- **Responsibilities**:
  - Detect if the input is from a terminal.
  - Display "Query? " prompt when appropriate to signal readiness for input.

### `tokenize_query()`
- **Description**: Converts the input string into a list of words, handling normalization.
- **Responsibilities**:
  - Dynamically allocate memory for an array to store the words.
  - Split the string based on spaces and punctuation.
  - Normalize words to a consistent case for processing.
  - Validate and discard any non-alphanumeric characters.

### `validate_user_query()`
- **Description**: Ensures the query adheres to the expected syntax for processing.
- **Responsibilities**:
  - Check for improper use of logical operators (AND, OR) at the beginning or end of the query.
  - Verify there are no consecutive logical operators.
  - Return a boolean indicating the query's validity.

## Query Execution

### `perform_lookup()`
- **Description**: Matches the query against the indexed data to find relevant documents.
- **Responsibilities**:
  - Utilize the index to retrieve potential document matches for each query term.
  - Apply logical operators to refine the match list based on the query structure.
  - Merge or intersect results as dictated by the presence of AND/OR operators.

### `intersect_counters()`
- **Description**: Handles the intersection of document sets when queries use AND.
- **Responsibilities**:
  - Compare two sets of counters, updating to reflect only documents present in both.

### `merge_counters()`
- **Description**: Manages the union of document sets for queries containing OR.
- **Responsibilities**:
  - Aggregate counts from multiple counter sets, ensuring all documents are represented.

## Results Display

### `rank_search_results()`
- **Description**: Orders and displays the results based on relevance.
- **Responsibilities**:
  - Calculate scores for each document based on frequency and distribution of query terms.
  - Sort documents by their scores in descending order.
  - Print the document ID, score, and snippet or URL for top results.

## Summary

The querier is a critical component of the TSE, enabling the user to interact with the indexed data through sophisticated search queries. The program is structured to efficiently handle and validate user input, execute queries against a large dataset, and return ranked results in an understandable format. This implementation ensures that the querier can effectively serve as the interface between the user and the data collected by the crawler and organized by the indexer. 
