#ifndef TRIE_H
#define TRIE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/* Node in Trie data structure */
typedef struct Trie Trie;

struct Trie {
    /* Array of pointers to the next Trie nodes */
    Trie** nodeList;
    /* Data stored by this node */
    void* data;

    /* Size of nodeList */
    size_t nodeListSize;
    /* Size of data */
    size_t dataSize;

    /* Flag for whether or not this node is an endpoint */
    bool endPoint;
};

/* Accepts the size of data stored in the trie
 * Returns a pointer to the newly initialized trie with no data in it */
Trie* initTrie(const size_t dataSize);

/* Frees all data contained within specified trie */
void deleteTrie(Trie* trie);

/* Accepts the trie to modify and the data point in the node to add
 * Returns a pointer to the added node */
Trie* addNode(Trie* trie, const void* data);

/* Accepts the trie to modify and an array of data pointers */
void addDataSequence(Trie* trie, void* const* sequence, const size_t sequenceSize);

/* Search for trie node that contains specified data point.
 * Returns pointer to node if found, NULL otherwise */
Trie* searchTrieData(const Trie* trie, const void* data);

/* Returns the pointer to a copy of src */
void* copyData(const void* src, size_t size);

/* Returns whether or not two void pointers have the same value */
bool compareData(const void* a, const void* b, size_t size);

/* Search through trie for occurence of data sequence */
bool searchTrieSequence(const Trie* trie, void* const* sequence, const size_t sequenceSize);

#endif
