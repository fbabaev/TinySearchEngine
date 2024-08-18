## Overview

The `crawler.c` module, part of Dartmouth's CS50 Tiny Search Engine project, crawls webpages starting from a seed URL. It fetches webpages, scans for links, and recursively processes found URLs up to a defined maximum depth.

#### Components

- **Headers and Libraries:**
  - Standard: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<unistd.h>`, `<sys/types.h>`, `<sys/stat.h>`
  - Custom: `bag.h`, `hashtable.h`, `webpage.h`, `pagedir.h`, `file.h`
  - `MAX_DEPTH`: Defines the crawl depth (maximum is 10).

- **`int main(int argc, char *argv[])`:**
  - Validates arguments.
  - Checks and prepares the page directory.
  - Initializes the bag for pages to crawl and hashtable for processed pages.
  - Creates the seed page and starts crawling.
  - Frees memory after crawling.

- **`void crawler(hashtable_t *processedPages, bag_t *toCrawl, char *pageDirectory, webpage_t *seedPage, int maxDepth)`:**
  - Inserts the seed page into the crawl queue.
  - Continuously extracts, fetches, and processes pages.
  - Saves fetched pages and scans them for new URLs.
  - Frees memory for non-seed pages.

- **`void pagescanner(hashtable_t *processedPages, bag_t *toCrawl, webpage_t *page, int maxDepth)`:**
  - Extracts and normalizes URLs from a page.
  - Checks for duplicates and valid internal URLs.
  - Adds new URLs to the crawl queue if within depth limits.

- **`inline static void logr(const char *action, char *url, int depth)`:**
  - Logs actions (e.g., finding, adding, ignoring URLs) during crawling.

## Usage

- **Build:** `make`
- **Run Tests:** `make test`
- **Clean Up:** `make clean`
