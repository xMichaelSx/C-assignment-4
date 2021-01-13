#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUM_LETTERS ((int)26)
#define INIT_WORD_LEN 100 // will be used for initial array(with calloc) of the words,
//                       if needed will be extended by realloc.

typedef enum {FALSE=0,TRUE=1} boolean;

typedef struct node {
    boolean end_word;
    char letter;
    long unsigned int count;
    struct node *children[NUM_LETTERS]; // makes 26 nodes at each level of the type: (struct node)
    } node;

int storeword(char *w, int arr_len, char *end);
node* newNode(char letter, long unsigned int count);
void insertWord(node **head, char *letters, int word_len);
void printTree(node *head, char *word_array, int arr_len, int index);
void printTreeReverse(node *head, char *word_array, int arr_len, int index);
void deleteTree(node **head);