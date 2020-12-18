This is a collection of functions that work together to act as a hashtable data sctructure.

Functions

    struct Performance *newPerformance()
        Creates a structure holding information about the efficiency of the array.
        
    struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void *, int), int (*compar)(const void *, const void *))
        Allocates memory for a new hashtable an initializes its values.
        
    void addElement(struct Performance *performance, struct HashTable *table, void *src)
        Adds an element to a pre-existing hashtable.
        
    int getIdx(struct Performance *performance, struct HashTable *table, void *src)
        Finds an element in the hashtable and returns its index.
        
    void freeTable(struct Performance *performancem, struct HashTable *table)
        Frees all the memory allocated to a hashtable.
        
    void *getElement(struct Performance *performance, struct HashTable *table, void *target)
        Returns an element inside the hashtable that matches the target.
        
    void removeElement(struct Performance *performance, struct HashTable *table, void *target)
        Removes the element from the hashtable that matches the target.
        
    int hashAccuracy(struct HashTable *table)
        Returns an integer that represents the sums of the differences between elements that have collided and their proper index.
        
    void rehash(struct HashTable *table)
        Moves elements around to increase the efficiency of the hashtable.

Files

    hash.c
        Contains all the functions in the library
        
    hash.h
        Contains all the function declarations for the functions in hash.c
        
    htest1.c - htest4.c
        A collection of main functions to be used to test the hashtable data structure
        
    names1.txt
        Text file containing values to load as hashtables for testing purposes

Usage (make)

    all
        Compiles all the functions for the library and creates test executables
        
    hash.o
        Compiles all the functions in hash.c into an object file
        
    htest1.o
        Creates object file htest1.o
        
    htest2.o
        Creates object file htest2.o
        
    htest3.o
        Creates object file htest3.o
        
    htest4.o
        Creates object file htest4.o
        
    htest1
        Creates executable file htest1
        
    test2
        Creates executable file htest2
        
    test3
        Creates executable file htest3
        
    test4
        Creates executable file htest4
        
    clean
        Deletes all compiles executables and object files
