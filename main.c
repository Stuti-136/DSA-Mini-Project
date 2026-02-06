#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

int main() {
    int k;
    root = createNode();

    loadDictionary("words.txt");

    char input[100];
    printf("\nEnter a prefix to get suggestions: ");
    scanf("%s", input);

    if (searchPrefix(input)) {
        printf("Prefix '%s' FOUND.\n", input);
        printf("Enter number of suggestions (k): ");
        scanf("%d", &k);
        getSuggestions(input,k);
    } else {
        printf("Prefix '%s' NOT found.\n", input);
    }

    int total = countWordsWithPrefix(root, input);
    printf("\nTotal words starting with \"%s\": %d\n", input, total);

    freeTrie(root);

    return 0;
}

