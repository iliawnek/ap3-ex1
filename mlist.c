#include "mlist.h"
#include "mentry.h"
#include <stdlib.h>

#define INITIAL_HASH_TABLE_SIZE 40 // double the specified 20

MList *expand_hash_table(MList **ml);

struct mlist {
    int buckets_filled;
    MEntry **hash_table; // todo: pointer to a pointer? pointer to an array?
};

unsigned int hash_table_size = INITIAL_HASH_TABLE_SIZE;
int ml_verbose = 0;

// Creates new mailing list.
MList *ml_create(void) {
    if (ml_verbose) fprintf(stderr, "ml_create()\n");
    MList *ml = malloc(sizeof(MList));
    if (ml == NULL) return NULL; // no space in memory for mailing list
    ml->buckets_filled = 0;
    ml->hash_table = calloc(hash_table_size, sizeof(MEntry));
    if (ml->hash_table == NULL) return NULL; // no space in memory for mailing list
    return ml;
}

// Adds entry to mailing list.
// Returns 1 if successful.
// Returns 1 if entry is duplicate.
// Returns 0 if error (malloc).
int ml_add(MList **ml, MEntry *me) {
    if (ml_verbose) fprintf(stderr, "ml_add()\n");
    if ((*ml)->buckets_filled == (hash_table_size / 2)) expand_hash_table(ml);
    unsigned int index = me_hash(me, hash_table_size);
    MEntry **hash_table = (*ml)->hash_table;
    MEntry *cursor;
    while (1) {
        cursor = hash_table[index];
        // found a space
        if (cursor == NULL) {
            hash_table[index] = me;
            (*ml)->buckets_filled++;
            return 1;
        }
        // trying to add duplicate
        if (cursor == me) return 1;
        // reached end of hash table, need to wrap round
        if (index == hash_table_size - 1) index = 0;
        else index++;
    }
}

// Looks for entry in mailing list.
// Returns matching entry if found.
// Returns NULL if not found.
MEntry *ml_lookup(MList *ml, MEntry *me) {
    if (ml_verbose) fprintf(stderr, "ml_lookup()\n");
    unsigned int index = me_hash(me, hash_table_size);
    MEntry **hash_table = ml->hash_table;
    MEntry *cursor;
    while (1) {
        cursor = hash_table[index];
        if (cursor == NULL) return NULL;
        if (me_compare(cursor, me) == 0) return cursor;
        if (index == hash_table_size - 1) index = 0;
        else index++;
    }
}

// Destroys mailing list.
void ml_destroy(MList *ml) {
    if (ml_verbose) fprintf(stderr, "ml_destroy()\n");
    MEntry **hash_table = ml->hash_table;
    MEntry *cursor;
    for (int i = 0; i < hash_table_size; i++) {
        cursor = hash_table[i];
        if (cursor != NULL) free(cursor);
    };
    free(ml);
}

MList *expand_hash_table(MList **ml) {
    if (ml_verbose) fprintf(stderr, "expand_hash_table()\n");
    hash_table_size *= 2;
    MList *new_ml = ml_create();
    MEntry **hash_table = (*ml)->hash_table;
    MEntry *cursor;
    for (int i = 0; i < hash_table_size; i++) {
        cursor = hash_table[i];
        if (cursor != NULL) {
            ml_add(&new_ml, cursor);
            free(cursor);
        }
    }
    free(ml);
    return new_ml;
}