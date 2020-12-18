#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __string_h_
#include <string.h>
#endif

#ifndef __stdlib_h_
#include <stdlib.h>
#endif

#ifndef __hash_h_
#include "hash.h"
#endif

// Allocates memory for the struct 'Performance' and initializes its values
struct Performance *newPerformance(){
    struct Performance *performance = malloc(sizeof(struct Performance));
    if(performance == NULL){
        fprintf(stderr, "The allocation for the Performance Struct has failed\n");
        exit(1);
    }
    performance -> reads = 0;
    performance -> writes = 0;
    performance -> mallocs = 0;
    performance -> frees = 0;
    return performance;
}

// Allocates memory for a new hashtable and initializes its values
struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void*, int), int (*compar)(const void*, const void*)){
    struct HashTable *hashTable = malloc(sizeof(struct HashTable));
    if(hashTable == NULL){
        fprintf(stderr, "createTable: The allocation for the HashTable struct has failed\n");
        free(performance);
        exit(1);
    }
    hashTable -> capacity = capacity;
    hashTable -> nel = 0;
    hashTable -> data = malloc(sizeof(void*) * capacity);
    if(hashTable -> data == NULL){
        fprintf(stderr, "createTable: The allocation for the data within the HashTable struct has failed\n");
        free(performance);
        free(hashTable);
        exit(1);
    }
    for(int i = 0; i < capacity; i++){
        (hashTable -> data)[i] = NULL;
        performance -> reads += 1;
    }
    hashTable -> hash = hash;
    hashTable -> compar = compar;
    performance -> mallocs += 1;
    return hashTable;
}

// Adds an element to a pre-existing hashtable
void addElement(struct Performance *performance, struct HashTable *table, void *src){
    if(table -> nel == table -> capacity){
        fprintf(stderr, "addElement: The hashtable is already full\n");
        free(performance);
        freeTable(performance, table);
    }
    int index = (table -> hash)(src, table -> capacity);
    while((table -> data)[index] != NULL){
        index += 1;
        if(index == table -> capacity){
            index = 0;
        }
        performance -> reads += 1;
    }
    (table -> data)[index] = src;
    table -> nel += 1;
    performance -> writes += 1;
}

// Gets the current index of an element inside of a hashtable
int getIdx(struct Performance *performance, struct HashTable *table, void *src){
    int startIndex = (table -> hash)(src, table -> capacity);
    int index = startIndex;
    int compared = -1;

    while(compared != 0){
        if((table -> data)[index] != NULL){
            compared = (table -> compar)(src, (table -> data)[index]);
            performance -> reads += 1;
        }
        if(compared == 0){
            return index;
        }else{
            index += 1;
            if(index == startIndex){
                return -1;
            }else if(index == table -> capacity){
                index = 0;
            }
        }
    }
    return -1;
}

// Frees all the memeory allocated to a hashtable
void freeTable(struct Performance *performance, struct HashTable *table){
    free(table -> data);
    free(table);
    performance -> frees += 1;
}

// Returns the element inside the hashtable that matches the target
void *getElement(struct Performance *performance, struct HashTable *table, void *target){
    int index = getIdx(performance, table, target);
    if (index == -1){
        return NULL;
    }else{
        return (table -> data)[index];
    }
}

// Removes the element from the hashtable that matches the target
void removeElement(struct Performance *performance, struct HashTable *table, void *target){
    int index = getIdx(performance, table, target);
    if(index != -1){
        (table -> data)[index] = NULL;
        performance -> writes += 1;
        table -> nel -= 1;
    }
}

// Returns an integer that represents the sums of the differences between elements that have collided and their proper index
int hashAccuracy(struct HashTable *table){
    int output = 0;
    for(int i = 0; i < table -> capacity; i++){
        if((table -> data)[i] != NULL){
            int index = (table -> hash)((table -> data)[i], table -> capacity);
            if(i > index){
                output += i - index;
            } else if (i < index){
                output += (table -> capacity) - index + i;
            }
        }
    }
    return output;
}

// Moves elements around to reduce the hashAccuracy number and therefore increase efficiency
void rehash(struct HashTable *table){
    int swapped;
    for (int i = 0; i < table -> capacity; i++){
       if((table -> data)[i] != NULL){
            int index = (table -> hash)((table -> data)[i], table -> capacity);
            if (i > index){
                for(int j = index; j < i; j++){
                    if((table -> data)[j] == NULL){
                        for(int y = j+1; y <= i; y++){
                            if((table -> data)[y] != NULL){
                                if((table -> hash)((table -> data)[y], table -> capacity) == index){
                                    (table -> data)[j] = (table -> data)[y];
                                    (table -> data)[y] = NULL;
                                }
                            }
                        }
                    }
                }
            } else if(i < index){
                swapped = i;
                for(int j = index; j <  table -> capacity; j++){
                    if((table -> data)[j] == NULL){
                        for(int y = j+1; y < table -> capacity; y++){
                            if((table -> data)[y] != NULL){
                                if((table -> hash)((table -> data)[y], table -> capacity) == index){
                                    (table -> data)[j] = (table -> data)[y];
                                    (table -> data)[y] = NULL;
                                }
                            }
                        }
                    }
                }
                for(int j = 0; j < i; j++){
                    if((table -> data)[j] == NULL){
                        for(int y = j+1; y <= i; y++){
                            if((table -> data)[y] != NULL){
                                if((table -> hash)((table -> data)[y], table -> capacity) == index){
                                    (table -> data)[j] = (table -> data)[y];
                                    (table -> data)[y] = NULL;
                                    swapped = j;
                                }
                            }
                        }
                    }
                }
                for(int j = index; j <  table -> capacity; j++){
                    if((table -> data)[j] == NULL){
                        (table -> data)[j] = (table -> data)[swapped];
                        (table -> data)[swapped] = NULL;
                    }
                }
            }
       }
    }
}