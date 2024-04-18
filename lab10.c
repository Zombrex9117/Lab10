#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count; 
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Initializes a trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->root = createNode();
    }
    return trie;
}

// Inserts the word into the trie
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    // Mark the end of the word
    current->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->count;
}

// Deallocates memory for the trie nodes
struct Trie *deallocateTrieHelper(struct TrieNode *root) {
    if (root == NULL) return NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            deallocateTrieHelper(root->children[i]);
        }
    }
    free(root);
    return NULL;
}

// Deallocates memory for the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) return NULL;
    pTrie->root = deallocateTrieHelper(pTrie->root);
    free(pTrie);
    return NULL;
}
// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE* inFile = fopen(filename, "r");
	if (inFile == NULL) return -1;

	int count =0;
	char word[100];
	fscanf(inFile, "%d\n", &count);
	for (int i=0; i<count; i++){
		fscanf(inFile, "%s\n", word);
		pInWords[i] = (char*)calloc(strlen(word), sizeof(char));
		strcpy(pInWords[i], word);

	}
	return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}