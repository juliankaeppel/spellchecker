#include <stdio.h>
#include <spellcheck.h>

int main(void) {
    /* SpellChecker object */
    Trie* spellChecker = initSpellChecker("enable1.txt");
    /* Pointer for word */
    char* word = malloc(sizeof(char));
    /* Active char */
    char ch;
    /* Stored length of word */
    int len;

    do {
        word = realloc(word, sizeof(char));
        word[0] = '\0';

        /* Load word from stdin */
        while ((ch = fgetc(stdin)) != '\n') {
            /* Reallocate word to be two more than the current strlen,
             * since a new char is being concatenated, and the null terminator must remain */
            word = realloc(word, (strlen(word) + 2) * sizeof(char));

            /* Store strlen to len so it doesn't change when word is modified */
            len = strlen(word);

            /* Add ch to end of word */
            word[len] = ch;
            word[len + 1] = '\0';
        }

        if (strlen(word) > 1 && !checkWord(spellChecker, word))
            puts("\tWord not recognized");
    } while (strlen(word) > 0);

    free(word);

    deleteSpellChecker(spellChecker);

    return 0;
}
