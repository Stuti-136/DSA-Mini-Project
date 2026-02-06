# DSA-Mini-Project
# Trie-based Word Suggestion System

## Development Workflow
1. insertWord()
2. searchPrefix()
3. loadDictionary()
4. getSuggestions()
5. countWordsWithPrefix()
6. freeTrie()

## File Structure
`trie.h` → Header file containing structure definitions and function declarations 
`trie.c` → Contains all the 6 functions
`main.c` → Loads dictionary, handles input, and displays suggestions  
`words.txt` → List of words used for suggestions

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
