#include "mentry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024 // todo: currently arbitrary; is there a better limit?
#define HASH_STRING_SIZE 128 // todo: currently arbitrary; is there a better limit?
#define LINES_PER_ENTRY 3

// todo: should this function be in mentry.c?
// todo: source 2
// Copies alphanumeric characters from source to destination.
// source is expected to end in \0.
// destination is expected to be large enough to hold source.
void remove_nonalnum(char source[], char destination[]) {
    int d = 0;
    for (int s = 0; source[s] != '\0'; s++)
        if (isalnum(source[s])) {
            destination[d] = source[s];
            d++;
        }
    destination[d] = '\0';
}

// todo: should this function be in mentry.c?
// Converts every char in source to lower.
void string_to_lower(char source[]) {
    for (int s = 0; source[s] != '\0'; s++) {
        source[s] = (char) tolower(source[s]);
    }
}

// Returns the next MEntry from fd.
// Returns NULL if EOF is reached.
MEntry *me_get(FILE *fd) {
    // allocate space in memory for new MEntry
    MEntry *me = malloc(sizeof(MEntry));
    char *surname = NULL;
    int *house_number = malloc(sizeof(int));
    char *postcode;
    char *full_address = malloc(BUFFER_SIZE); // todo: is there a better way?

    // todo: break up into individual functions?
    // read file
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < LINES_PER_ENTRY; i++) {
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
// Computes hash of MEntry mod size.
unsigned long me_hash(MEntry *me, unsigned long size) {
    char s[HASH_STRING_SIZE]; // todo: should I be using BUFFER_SIZE here?
    sprintf(s, "%s%s%d", me->surname, me->postcode, me->house_number);
    char c;
    unsigned hash = 0;
    for (int i = 0; (c = s[i]) != '\0'; i++) {
        hash = c + 31 * hash;
    }
    return hash % size;
}

// Prints MEntry in original formatting to fd.
void me_print(MEntry *me, FILE *fd) {
    fprintf(fd, me->full_address);
}