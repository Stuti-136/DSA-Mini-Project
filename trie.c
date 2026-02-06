#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

struct TrieNode* root;

// Function to create new trie node
struct TrieNode* createNode() {
    struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->child[i] = NULL;
    return node;
}

// 1. Insert a word
void insertWord(const char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        char ch = tolower(word[i]);
        if (ch < 'a' || ch > 'z') {
            printf("Invalid word insertion.\n");
            exit(1);
        }
        int index = ch - 'a';  //'a'->0, 'b'->1, etc.
        if (current->child[index] == NULL)
            current->child[index] = createNode();
        current = current->child[index];
    }
    current->end_of_word = 1;  //mark end of word
}

// 2. Search if prefix exists in trie
int searchPrefix(const char *prefix) {
    struct TrieNode *current = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        char ch = tolower(prefix[i]);  //convert to lower case
        if (ch < 'a' || ch > 'z') {
            printf("No special characters or numbers allowed.\n");
            return 0;
        }
        int index = ch - 'a';
        if (current->child[index] == NULL)
            return 0;  // prefix does not exist
        current = current->child[index];
    }
    return 1;  //prefix exists
}

// 3. Implementation of loadDictionary()
void loadDictionary(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char word[WORD_LIMIT];
    int count = 0;

    while (fscanf(file, "%s", word) != EOF) {
        insertWord(word);
        count++;
    }

    fclose(file);
    printf("Loaded %d words from %s successfully.\n", count, filename);
}

// Helper function to collect suggestions recursively
void collectWords(struct TrieNode* node, char* prefix, int k, char results[][WORD_LIMIT], int* count) {
    if (*count >= k) return;

    if (node->end_of_word) {
        strcpy(results[*count], prefix);
        (*count)++;
        if (*count >= k) return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->child[i] != NULL) {
            char nextChar = 'a' + i;
            int len = strlen(prefix);
            prefix[len] = nextChar;
            prefix[len + 1] = '\0';
            collectWords(node->child[i], prefix, k, results, count);
            prefix[len] = '\0'; // backtrack
        }
    }
}

// 4. Implementation of getSuggestions()
void getSuggestions(const char* prefix, int k) {
    struct TrieNode* current = root;

    // Traverse the Trie according to prefix
    for (int i = 0; prefix[i] != '\0'; i++) {
        char c = tolower(prefix[i]);
        if (!isalpha(c)) continue;
        int index = c - 'a';
        if (current->child[index] == NULL) {
            printf("No suggestions found for \"%s\"\n", prefix);
            return;
        }
        current = current->child[index];
    }

    // Prepare temporary variables
    char tempPrefix[WORD_LIMIT];
    strcpy(tempPrefix, prefix);

    char results[MAX_WORDS][WORD_LIMIT];
    int count = 0;

    // Collect top-k words
    collectWords(current, tempPrefix, k, results, &count);

    // Print results
    if (count == 0) {
        printf("No suggestions found for \"%s\"\n", prefix);
    } else {
        printf("\nSuggestions for prefix \"%s\":\n", prefix);
        for (int i = 0; i < count; i++)
            printf("%d. %s\n", i + 1, results[i]);
    }
}

// 5. Free all Trie nodes (memory cleanup)
void freeTrie(struct TrieNode* node) {
    if (node == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(node->child[i]);
    free(node);
}

// 6. Count total words with a given prefix
int countWordsWithPrefix(struct TrieNode* node, const char* prefix) {
    // Traverse to the node that ends the prefix
    struct TrieNode* current = node;
    for (int i = 0; prefix[i] != '\0'; i++) {
        char c = tolower(prefix[i]);
        if (!isalpha(c)) return 0;
        int index = c - 'a';
        if (current->child[index] == NULL)
            return 0;
        current = current->child[index];
    }

    // Now count all words in the subtree of this prefix node
    int count = 0;
    // Helper lambda-style recursion inside C
    void dfs(struct TrieNode* n) {
        if (n == NULL) return;
        if (n->end_of_word) count++;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (n->child[i]) dfs(n->child[i]);
    }
    dfs(current);
    return count;
}

