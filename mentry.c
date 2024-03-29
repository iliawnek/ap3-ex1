// Name: Ken Li
// Matriculation number: 2131620
// Assignment: APH Exercise 1

// This is my own work as defined in the Academics Ethics agreement I have signed,
// with the exception of me_hash(), which was adapted from the book
// The C Programming Language (2nd edition), page 144.

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mentry.h"

#define BUFFER_SIZE 1024 // limit for buffer string when reading from file in me_get()
#define ADDRESS_LIMIT 1024 // limit for number of chars in each entry's full_address
#define ID_SIZE 128 // size of temporary id string for individual MEntry
#define LINES_PER_ENTRY 3 // lines of input file per mailing list entry

// todo: source 2
// Copies alphanumeric characters from source to destination.
// source is expected to end in \0.
// destination is expected to be large enough to hold source.
void remove_nonalnum(char source[], char destination[]) {
    int d = 0;
    int s;
    for (s = 0; source[s] != '\0'; s++)
        if (isalnum(source[s])) {
            destination[d] = source[s];
            d++;
        }
    destination[d] = '\0';
}

// Converts every char in source to lower.
void string_to_lower(char source[]) {
    int s;
    for (s = 0; source[s] != '\0'; s++) {
        source[s] = (char) tolower(source[s]);
    }
}

// Sets destination string to surname + postcode + house_number of mailing list entry.
// Used for hashing and comparison of mailing list entries.
void me_get_id(MEntry *me, char *destination) {
    sprintf(destination, "%s%s%d", me->surname, me->postcode, me->house_number);
}

// Returns next mailing list entry from input fd.
// Returns NULL if EOF is reached.
MEntry *me_get(FILE *fd) {
    // allocate space in memory for new MEntry
    MEntry *me = malloc(sizeof(MEntry));
    char *surname = NULL;
    int *house_number = malloc(sizeof(int));
    char *postcode;
    char *full_address = malloc(ADDRESS_LIMIT);

    // read file
    char buffer[BUFFER_SIZE];
    int i;
    for (i = 0; i < LINES_PER_ENTRY; i++) {
        // stop and free space from memory if EOF is reached
        if (fgets(buffer, BUFFER_SIZE, fd) == NULL) {
            free(me);
            free(house_number);
            free(full_address);
            if (surname != NULL) free(surname);
            return NULL;
        }
        // handle name line
        if (i == 0) {
            surname = malloc(strlen(buffer) * sizeof(char));
            sscanf(buffer, "%[^,]", surname); // todo: source 1
            string_to_lower(surname);
            me->surname = surname;
            strcpy(full_address, buffer);
        }
        // handle address line
        else if (i == 1) {
            if (sscanf(buffer, "%d", house_number) != 0) {
                me->house_number = *house_number;
            } else {
                me->house_number = 0; // defaults to 0 if no house number is found
            }
            free(house_number);
            strcat(full_address, buffer);
        }
        // handle postcode line
        else if (i == 2) {
            postcode = malloc(strlen(buffer) * sizeof(char));
            remove_nonalnum(buffer, postcode);
            string_to_lower(postcode);
            me->postcode = postcode;
            strcat(full_address, buffer);
        }
    }
    me->full_address = full_address;
    return me;
};

// todo: source 3
// Computes hash of mailing list entry mod size.
unsigned long me_hash(MEntry *me, unsigned long size) {
    char id[ID_SIZE];
    me_get_id(me, id);
    char c;
    unsigned long hash = 0;
    int i;
    for (i = 0; (c = id[i]) != '\0'; i++) {
        hash = c + 31 * hash;
    }
    return hash % size;
}

// Prints mailing list entry in original formatting to output fd.
void me_print(MEntry *me, FILE *fd) {
    fprintf(fd, me->full_address);
}

// Compares me1 and me2.
// Returns < 0 if me1 < me2.
// Returns 0 if me1 == me2.
// Returns > 0 if me1 > me2.
int me_compare(MEntry *me1, MEntry *me2) {
    char id1[ID_SIZE]; // todo: should I be using ID_SIZE here?
    char id2[ID_SIZE]; // todo: should I be using ID_SIZE here?
    me_get_id(me1, id1);
    me_get_id(me2, id2);
    return strcmp(id1, id2);
}

// Destroys mailing list entry and frees all memory allocated to it and its members.
void me_destroy(MEntry *me) {
    // todo: am I forgetting to free anything else here?
    free(me->surname);
    free(me->postcode);
    free(me->full_address);
    free(me);
}
