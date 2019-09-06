#include <spellcheck.h>

Trie* initSpellChecker(const char* wordList) {
    /* file pointer */
    FILE* fp;
    /* Active char being read from file */
    char ch;
    /* Pointer to data in trie-readable format */
    void** data = NULL;
    /* Size of data */
    size_t dataSize = 0;
    /* Pointer to trie being used, with chars as data type */
    Trie* trie = initTrie(sizeof(char), NULL, NULL);

    size_t i;

    /* Open wordList to be read from */
    fp = fopen(wordList, "r");

    /* Make sure file has been successfully opened */
    if (!fp) {
        perror ("Error opening word list for spell checking.\n");
        exit(EXIT_FAILURE);
    }

    /* Loop through file char by char until EOF is reached */
    while ((ch = fgetc(fp)) != EOF) {
        /* End and submit word when line-break is reached */
        if (ch == '\n') {
            /* Submit data */
            addDataSequence(trie, data, dataSize);
            /* Free elements in data */
            for (i = 0; i < dataSize; i++) free(data[i]);
            dataSize = 0;
        } else {
            /* Create a new slot in data */
            dataSize++;
            data = realloc(data, dataSize * sizeof(void*));
            /* Allocate space in data slot since ch isn't const */
            data[dataSize - 1] = malloc(sizeof(char));
            /* Store ch into newly created data slot */
            *(char*)data[dataSize - 1] = ch;
        }
    }

    /* Check for value in data in case wordList doesn't end with newline */
    if (dataSize) {
        /* Submit data */
        addDataSequence(trie, data, dataSize);
        /* Free elements in data */
        for (i = 0; i < dataSize; i++) free(data[i]);
        dataSize = 0;
    }

    /* Free data itself */
    free(data);

    /* Close file once done reading */
    fclose(fp);

    return trie;
}

void deleteSpellChecker(Trie* trie) {
    deleteTrie(trie);
}

bool checkWord(const Trie* trie, const char* word) {
    /* DataSize is equal to the word length */
    size_t dataSize = strlen(word);
    /* Data in format usable by trie */
    void** data = malloc(dataSize * sizeof(void*));

    size_t i;

    /* Result must be stored so data can be freed before returning */
    bool result;

    for (i = 0; i < dataSize; i++) {
        /* New space must be allocated since word is const */
        data[i] = malloc(sizeof(char));
        /* Letter is converted to lowercase for checking */
        *(char*)data[i] = tolower(word[i]);
    }

    result = searchTrieSequence(trie, data, dataSize);

    /* Free elements in data */
    while (dataSize--) free(data[dataSize]);
    /* Free data */
    free(data);

    return result;
}
