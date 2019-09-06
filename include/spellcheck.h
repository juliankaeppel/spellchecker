#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <trie.h>

/* Creates a trie with every word from wordList in it */
Trie* initSpellChecker(const char* wordList);

/* Clears data allocated by initSpellChecker */
void deleteSpellChecker(Trie* trie);

/* Check if word is contained within trie */
bool checkWord(const Trie* trie, const char* word);

#endif
