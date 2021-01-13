#include "trie.h"
#include <stdio.h>

int main(int argc, char **argv){ 

    node *head = NULL;
    head = newNode(0,0);
    char end[1] = {0};
    int word_len = 0;
    char *word = NULL;
    while(end[0] != -1){    // while not reached EOF          
        word = (char*)calloc(INIT_WORD_LEN, sizeof(char));
        word_len = storeword(word,INIT_WORD_LEN,end);
        if (word_len == -2){
            free(word);
            word = NULL;
            break;    // indicates EOF
        } 
        if (word_len == -3){
            free(word);
            word = NULL;
            continue; // indicates some char that does not fit the profile (continuing to next word)
        } 
        insertWord(&head,word,word_len);
        free(word);
        word = NULL;
    }
    char *word2 = NULL;
    word2 = (char*)calloc(INIT_WORD_LEN, sizeof(char));

    if (argc == 1){
        printTree(head,word2,INIT_WORD_LEN,0);
        free(word2);
        word2 = NULL;    
    }
    else if (*argv[1] == 'r'){
        printTreeReverse(head,word2,INIT_WORD_LEN,0);
        free(word2);
        word2 = NULL;
    }
    deleteTree(&head);
    
    return 0;
}