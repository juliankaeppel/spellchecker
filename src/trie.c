#include <trie.h>

Trie* initTrie(const size_t dataSize,
        void* (*copyFunc)(const void* src, size_t size),
        bool (*compFunc)(const void* a, const void* b, size_t size)) {
    Trie* trie = malloc(sizeof(Trie));
    
    trie->nodeList = NULL;
    trie->nodeListSize = 0;
    trie->data = NULL;
    trie->dataSize = dataSize;
    trie->endPoint = false;
    if (copyFunc) trie->copyFunc = copyFunc;
    else trie->copyFunc = copyData;
    if (compFunc) trie->compFunc = compFunc;
    else trie->compFunc = compData;

    return trie;
}

void deleteTrie(Trie* trie) {
    size_t i;

    /* Free data pointer */
    free(trie->data);

    /* Repeat recursively */
    for (i = 0; i < trie->nodeListSize; i++)
        deleteTrie(trie->nodeList[i]);

    /* Free nodeList once its contents have been cleared, assuming it exists */
    if (trie->nodeList)
        free(trie->nodeList);

    /* Free the node itself */
    free(trie);
}

Trie* addNode(Trie* trie, const void* data) {
    /* Store current value of nodeListSize to be used as index */
    size_t index = trie->nodeListSize;

    /* Allocate space for a new node */
    trie->nodeListSize++;
    trie->nodeList = realloc(trie->nodeList, trie->nodeListSize * sizeof(Trie*));
    /* Set new node */
    trie->nodeList[index] = initTrie(trie->dataSize, trie->copyFunc, trie->compFunc);

    /* Copy data into new node */
    trie->nodeList[index]->data = trie->copyFunc(data, trie->dataSize);

    return trie->nodeList[index];
}

void addDataSequence(Trie* trie, void* const* sequence, const size_t sequenceSize) {
    size_t i;
    Trie* node = trie;
    Trie* temp;
    
    /* Loop through each element in sequence */
    for (i = 0; i < sequenceSize; i++) {
        /* Set the return of searchTrieData to temp so that it can be evaluated */
        temp = searchTrieData(node, sequence[i]);

        /* If temp isn't null, set node and progress to the next element in sequence
         * Otherwise, add a new node */
        if (temp) node = temp;
        else node = addNode(node, sequence[i]);
    }

    node->endPoint = true;
}

Trie* searchTrieData(const Trie* trie, const void* data) {
    size_t i;

    /* Loop through each node and return pointer to trie if it's data matches the input */
    for (i = 0; i < trie->nodeListSize; i++)
        if (trie->compFunc(trie->nodeList[i]->data, data, trie->dataSize)) return trie->nodeList[i];

    /* If no matching node is found, return NULL */
    return NULL;
}

void* copyData(const void* src, size_t size) {
    /* Cast src to char pointer */
    char* srcByte = (char*)src;
    /* Allocate size bytes for destByte */
    char* destByte = malloc(size);

    /* Copy each byte from srcByte to destByte */
    while (size--) destByte[size] = srcByte[size];

    return destByte;
}

bool compData(const void* a, const void* b, size_t size) {
    /* Cast a and b to char pointers */
    char* aByte = (char*)a;
    char* bByte = (char*)b;

    /* If any bytes in aByte and bByte don't match, return false */
    while (size--) if (aByte[size] != bByte[size]) return false;
    /* If end of loop is reached, a and b are equal; return true */
    return true;
}

bool searchTrieSequence(const Trie* trie, void* const* sequence, const size_t sequenceSize) {
    size_t i;
    const Trie* node = trie;
    Trie* temp;

    /* Progress through the sequence, checking that each term exists */
    for (i = 0; i < sequenceSize; i++) {
        temp = searchTrieData(node, sequence[i]);

        /* If node wasn't found, return false immediately */
        if (!temp) return false;

        /* Set node to temp after checking that it exists */
        node = temp;
    }

    /* Once the sequence has been located, return whether or not it contains an end point */
    return node->endPoint;
}
