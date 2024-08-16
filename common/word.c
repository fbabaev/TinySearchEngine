/*
 * word.c - 'word' module
 *
 * This module provides functionality to normalize a word by converting all its characters to lowercase.
 *
 * Firdavskhon Babaev
 * Date: May 6, 2024
 */

#include <ctype.h>
#include <string.h>

void normalizeWord(char *word) {
    if (word == NULL) {
        return;
    }

    for (int i = 0; word[i]; i++) {
        word[i] = tolower((unsigned char) word[i]);
    }
}
