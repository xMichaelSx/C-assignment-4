#include "trie.h"

int storeword(char *w, int arr_len, char *end){

    int word_len = 0;
    char c = getchar();
    if (c == EOF){
        return -2;
    }
    for(int i=0; ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) && c != EOF ;i++){

        if(i == arr_len-1){
            w = (char*) realloc(w, INIT_WORD_LEN); // reallocating with 100 more space (from defined)
            if (!w) printf("could not allocate space for the given long word, aborting word");
            return -3;
        }

        if (c >= 65 && c <= 90){
            c = tolower(c); // or just add 32 to the char to get the lower character.
        }
        w[i] = c;
        word_len++;
        c = getchar();
    }

    // for(int i = 0; i<word_len; i++){
    //     printf("%c",w[i]);
    // }
    // printf(" %d\n",word_len);
    // printf("\n");

    if (c == EOF) end[0] = -1; // to indicate EOF (to stop loop from continuing getting words)
    if (word_len == 0){
        return -3;
    }
    return word_len;
}

node* newNode(char letter, long unsigned int count){

    node *p = NULL;
    p = (node*)malloc(sizeof(node));
    if (p){
        p->letter = letter;
        p->count = count;
        p->end_word = FALSE; // always make then false, and the insert func will make the last node (the leaf) TRUE
        for(int i=0; i<NUM_LETTERS; i++){
            p->children[i] = NULL;
        }
    }
    else{
        printf("malloc failed to allocate space for new node, returning null");
        return NULL;
    }
    return p;
}

void insertWord(node **head, char *letters, int word_len){

    node *runner = *head;
    for(int i=0; i<word_len; i++){

        int idx = letters[i] - 'a'; // will get the index where to put the char at the alphabetical place node
        if (!(runner->children[idx])){
            runner->children[idx] = newNode(letters[i],0);
        }
        runner = runner->children[idx];
        
    }
    runner->end_word = TRUE; // last one is a leaf which indicates the end of the word
    runner->count += 1;      // counts how much words like this exist
}

// As the trie is alphabetically sorted, we need to an array
// to save the prefixes of simmilar words and the counter
// which indicates where to write the next chars of the next
// words and to indicate a stop sigh for the printing. (otherwise its a tedious work to print alphabetically)
void printTree(node *head, char *word_array, int arr_len, int index){

    for(int i=0; i<NUM_LETTERS;i++){

        if(i == arr_len-1){
            word_array = (char*)realloc(word_array, INIT_WORD_LEN); // reallocating with 100 more space (from defined)
            if (!word_array){
                printf("could not allocate space for the given long word, aborting print");
                return;
            }
            arr_len+=INIT_WORD_LEN;
        }

        if(head->children[i]){
            word_array[index] = head->children[i]->letter;
            printTree(head->children[i], word_array, arr_len, index+1);
        }
    }
    if(head->end_word == TRUE){
            for (int i = 0; i < index; i++){
                printf("%c",word_array[i]);
            }
            printf(" %ld\n",head->count);
    }
}

void printTreeReverse(node *head, char *word_array, int arr_len, int index){ // work with prefix maybe

    for(int i=NUM_LETTERS-1; i>=0;i--){

        if(i == arr_len-1){
            word_array = (char*)realloc(word_array, INIT_WORD_LEN); // reallocating with 100 more space (from defined)
            if (!word_array){
                printf("could not allocate space for the given long word, aborting print");
                return;
            }
            arr_len+=INIT_WORD_LEN;
        }

        if(head->children[i]){
            word_array[index] = head->children[i]->letter;
            printTreeReverse(head->children[i], word_array, arr_len, index+1);
        }
    }
    if(head->end_word == TRUE){
            for (int i = 0; i < index; i++){
                printf("%c",word_array[i]);
            }
            printf(" %ld\n",head->count);
    }
}

void deleteTree(node **head){

    if(*head == NULL) return;

    for(int i=0; i<NUM_LETTERS;i++){
            deleteTree(&((*head)->children[i]));
            if(i == NUM_LETTERS-1){
                free(*head);
                *head = NULL;
            }
        }
}

