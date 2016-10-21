// Name: Ken Li
// Matriculation number: 2131620
// Assignment: APH Exercise 1

// This is my own work as defined in the Academics Ethics agreement I have signed.

#include "mlist.h"
#include <stdlib.h>

#define BUCKET_CAPACITY 20 // defined by specification
#define INITIAL_HASH_TABLE_SIZE 100
#define HASH_TABLE_EXPANSION_FACTOR 2 // defined by specification

void expand_hash_table(MList **ml, int factor);

// bucket's linked list node, pointing to a mailing list entry
typedef struct bucketitem {
    MEntry *me;
    struct bucketitem *next;
} BucketItem;

// bucket of the hash table pointing to a linked list
typedef struct bucket {
    BucketItem *first;
    int size;
} Bucket;

// mailing list storing pointers to entries within hash table
struct mlist {
    Bucket **hash_table;
};

unsigned int hash_table_size = INITIAL_HASH_TABLE_SIZE; // current size of hash table
int ml_verbose = 0; // if 1, print diagnostics to stderr

// Creates new mailing list.
MList *ml_create(void) {
    if (ml_verbose) fprintf(stderr, "Creating new mailing list.\n");

    // allocate memory for mailing list
    MList *ml = malloc(sizeof(MList));
    if (ml == NULL) {
        if (ml_verbose) fprintf(stderr, "Error: no space in memory for new mailing list.\n");
        return NULL;
    }

    // allocate memory for mailing list's hash table
    ml->hash_table = calloc(hash_table_size, sizeof(Bucket *));
    if (ml->hash_table == NULL) {
        if (ml_verbose) fprintf(stderr, "Error: no space in memory for new mailing list.\n");
        return NULL;
    }

    return ml;
}

// Adds entry to mailing list.
// Returns 1 if successful.
// Returns 1 if entry is duplicate.
// Returns 0 if error (malloc).
int ml_add(MList **ml, MEntry *me) {
    // get corresponding hash bucket
    Bucket **hash_table = (*ml)->hash_table;
    unsigned int index = me_hash(me, hash_table_size);
    if (ml_verbose) fprintf(stderr, "Adding entry with hash %d.\n", index);
    Bucket *bucket = hash_table[index];

    // if no bucket exists yet, create new one
    if (bucket == NULL) {
        if (ml_verbose) fprintf(stderr, "Bucket doesn't exist yet, creating a new one.\n");

        bucket = malloc(sizeof(Bucket));
        BucketItem *bucket_item = malloc(sizeof(BucketItem));
        if (bucket == NULL || bucket_item == NULL) {
            if (ml_verbose) fprintf(stderr, "Error: no space in memory for new bucket.\n");
            return 0;
        }

        bucket_item->me = me;
        bucket_item->next = NULL;
        bucket->first = bucket_item;
        bucket->size = 1;
        hash_table[index] = bucket;
        return 1;
    }

    // if bucket is full, expand hash table
    if (bucket->size == BUCKET_CAPACITY) {
        if (ml_verbose) fprintf(stderr, "Bucket at index %d is full.\n", index);
        expand_hash_table(ml, HASH_TABLE_EXPANSION_FACTOR);
        return ml_add(ml, me); // try adding entry to expanded hash table
    }

    // if duplicate entry exists, return without adding
    if (ml_lookup(*ml, me) != NULL) {
        if (ml_verbose) fprintf(stderr, "Duplicate entry found.\n");
        return 1;
    }

    // else, add entry to bucket
    BucketItem *bucket_item = malloc(sizeof(BucketItem));
    bucket_item->me = me;
    bucket_item->next = bucket->first;
    bucket->first = bucket_item;
    bucket->size++;
    return 1;
}

// Looks for entry in mailing list.
// Returns matching entry if found.
// Returns NULL if not found.
MEntry *ml_lookup(MList *ml, MEntry *me) {
    // get corresponding hash bucket
    unsigned int index = me_hash(me, hash_table_size);
    Bucket **hash_table = ml->hash_table;
    if (ml_verbose) fprintf(stderr, "Looking up entry with hash %d -> ", index);
    Bucket *bucket = hash_table[index];

    // if bucket doesn't exist, entry not found
    if (bucket == NULL) {
        if (ml_verbose) fprintf(stderr, "entry not found.\n");
        return NULL;
    }

    // iterate through linked list and look for entry
    BucketItem *cursor = bucket->first;
    do {
        if (me_compare(cursor->me, me) == 0) {
            if (ml_verbose) fprintf(stderr, "entry found.\n");
            return cursor->me;
        }
    } while ((cursor = cursor->next) != NULL);

    // bucket exists, but entry not found
    if (ml_verbose) fprintf(stderr, "entry not found.\n");
    return NULL;
}

// Destroys mailing list.
void ml_destroy(MList *ml) {
    if (ml_verbose) fprintf(stderr, "Destroying mailing list.\n");

    // traverse through hash table, deallocate memory for all pointers
    Bucket **hash_table = ml->hash_table;
    Bucket *bucket;
    BucketItem *bucket_item;
    BucketItem *next_bucket_item;
    int i;
    for (i = 0; i < hash_table_size; i++) {
        bucket = hash_table[i];
        if (bucket != NULL) {
            bucket_item = bucket->first;
            do {
                free(bucket_item->me);
                next_bucket_item = bucket_item->next;
                free(bucket_item);
            } while ((bucket_item = next_bucket_item) != NULL);
            free(bucket);
        }
    }
    free(hash_table);
    free(ml);
}

// Expands MList hash table by multiplying size by given factor.
void expand_hash_table(MList **ml, int factor) {
    // create new expanded MList
    hash_table_size *= factor;
    if (ml_verbose) fprintf(stderr, "Expanding hash table to %d buckets.\n", hash_table_size);
    MList *new_ml = ml_create();

    // add all existing entries to new MList, then destroy old MList
    Bucket **hash_table = (*ml)->hash_table;
    Bucket *bucket;
    BucketItem *bucket_item;
    BucketItem *next_bucket_item;
    int i;
    for (i = 0; i < hash_table_size / factor; i++) {
        bucket = hash_table[i];
        if (bucket != NULL) {
            bucket_item = bucket->first;
            do {
                ml_add(&new_ml, bucket_item->me);
                next_bucket_item = bucket_item->next;
                free(bucket_item);
            } while ((bucket_item = next_bucket_item) != NULL);
            free(bucket);
        }
    }
    free(hash_table);
    free(*ml);

    // old MList is now new Mlist
    *ml = new_ml;
}