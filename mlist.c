#include "mlist.h"
#include "mentry.h"
#include <stdlib.h>

#define BUCKET_CAPACITY 20 // hash table resizes if any bucket exceeds this size
#define INITIAL_HASH_TABLE_SIZE 100

void expand_hash_table(MList **ml);

typedef struct bucketitem {
    MEntry *me;
    struct bucketitem *next;
} BucketItem;

typedef struct bucket {
    BucketItem *first;
    int size;
} Bucket;

struct mlist {
    Bucket **hash_table; // todo: pointer to a pointer? pointer to an array?
};

unsigned int hash_table_size = INITIAL_HASH_TABLE_SIZE;
int ml_verbose = 0;

// Creates new mailing list.
MList *ml_create(void) {
    if (ml_verbose) fprintf(stderr, "ml_create()\n");
    MList *ml = malloc(sizeof(MList));
    if (ml == NULL) return NULL; // no space in memory for ew mailing list
    ml->hash_table = calloc(hash_table_size, sizeof(Bucket));
    if (ml->hash_table == NULL) return NULL; // no space in memory for new mailing list
    return ml;
}

// Adds entry to mailing list.
// Returns 1 if successful.
// Returns 1 if entry is duplicate.
// Returns 0 if error (malloc).
int ml_add(MList **ml, MEntry *me) {
    if (ml_verbose) fprintf(stderr, "ml_add()\n");

    Bucket **hash_table = (*ml)->hash_table;
    unsigned int index = me_hash(me, hash_table_size);
    Bucket *bucket = hash_table[index];

    // no bucket yet
    if (bucket == NULL) {
        bucket = malloc(sizeof(Bucket));
        if (bucket == NULL) return 0; // no space in memory for new bucket
        BucketItem *bucket_item = malloc(sizeof(BucketItem));
        if (bucket_item == NULL) return 0;  // no space in memory for new bucket
        bucket_item->me = me;
        bucket_item->next = NULL;
        bucket->first = bucket_item;
        bucket->size = 1;
        return 1;
    }

    // bucket is full
    if (bucket->size == BUCKET_CAPACITY) {
        expand_hash_table(ml);
        return ml_add(ml, me); // try adding entry to expanded hash table
    }

    // check for duplicate
    BucketItem *cursor = bucket->first;
    do {
        if (me_compare(cursor->me, me) == 0) return 1;
    } while ((cursor = cursor->next) != NULL);

    // add entry to bucket
    BucketItem *bucket_item = malloc(sizeof(BucketItem));
    bucket_item->me = me;
    bucket_item->next = bucket->first;
    bucket->first = bucket_item;
    bucket->size++; // todo: make sure this line works
    return 1;
}

// Looks for entry in mailing list.
// Returns matching entry if found.
// Returns NULL if not found.
MEntry *ml_lookup(MList *ml, MEntry *me) {
    if (ml_verbose) fprintf(stderr, "ml_lookup()\n");

    unsigned int index = me_hash(me, hash_table_size);
    Bucket **hash_table = ml->hash_table;
    Bucket *bucket = hash_table[index];

    if (bucket == NULL) return NULL; // bucket doesn't exist, therefore no entry

    BucketItem *cursor = bucket->first;
    do {
        if (me_compare(cursor->me, me) == 0) return me;
    } while ((cursor = cursor->next) != NULL);
    return NULL; // bucket exists, but entry not found
}

// Destroys mailing list.
void ml_destroy(MList *ml) {
    if (ml_verbose) fprintf(stderr, "ml_destroy()\n");

    Bucket **hash_table = ml->hash_table;
    Bucket *bucket;
    BucketItem *bucket_item;
    BucketItem *next_bucket_item;
    for (int i = 0; i < hash_table_size; i++) {
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
    free(ml);
}

void expand_hash_table(MList **ml) {
    if (ml_verbose) fprintf(stderr, "expand_hash_table()\n");

    hash_table_size *= 2;
    MList *new_ml = ml_create();
    Bucket **hash_table = (*ml)->hash_table;
    Bucket *bucket;
    BucketItem *bucket_item;
    BucketItem *next_bucket_item;
    for (int i = 0; i < hash_table_size; i++) {
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
    free(*ml);
    *ml = new_ml;
}