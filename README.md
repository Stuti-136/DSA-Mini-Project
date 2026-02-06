# DSA-Mini-Project
# Trie-based Word Suggestion System
This project implements a dictionary-based word suggestion system using the Trie data structure. The program loads words from `words.txt`, inserts them into a Trie, and then provides auto-suggestions based on user input.

## Features
1. Efficient prefix-based word search
2. Dynamic word suggestion
3. Counts number of words matching the prefix
4. Proper memory management using Trie cleanup
   
## Development Workflow
1. insertWord() - Inserts words into the trie
2. searchPrefix() - Finds the node corresponding to the given prefix
3. loadDictionary() - Loads words from `words.txt`
4. getSuggestions() - Retrieves all words matching the prefix
5. countWordsWithPrefix() - Counts total matching words
6. freeTrie() - Frees allocated trie memory

## File Structure
`trie.h` - Header file containing structure definitions and function declarations 
`trie.c` - Contains all Trie related functions
`main.c` - Loads dictionary, handles input, and displays suggestions  
`words.txt` - Dictionary file containing list of words used for suggestions

## How to Compile
Use the following command:
gcc main.c trie.c -o trie

## How to Run
./trie

## How It Works
1. Words from `words.txt` are inserted into a Trie.
2. The user enters a prefix.
3. The program:
   - Finds the prefix node using `searchPrefix()`
   - Collects matching words using `getSuggestions()`
   - Counts total matching words using `countWordsWithPrefix()`
4. The Trie is freed with `freeTrie()` at the end.
