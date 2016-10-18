#include "mentry.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024 // todo: currently arbitrary; is there a better limit?
#define LINES_PER_ENTRY 3

// todo: source 2
// Copies only non-space characters from source to destination.
// source is expected to end in \0.
// destination is expected to be large enough to hold source.
void delete_spaces(char source[], char destination[]) {
    int d = 0;
    for (int s = 0; source[s] != '\0'; s++)
        if (source[s] != ' ') {
            destination[d] = source[s];
            d++;
        }
    destination[d] = '\0';
}

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
    MEntry *mentry = malloc(sizeof(MEntry));
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
            free(mentry);
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
            mentry->surname = surname;
            strcpy(full_address, buffer);
        }
        // handle address line
        else if (i == 1) {
            if (sscanf(buffer, "%d", house_number) != 0) {
                mentry->house_number = *house_number;
            } else {
                mentry->house_number = 0; // defaults to 0 if no house number is found
            }
            free(house_number);
            strcat(full_address, buffer);
        }
        // handle postcode line
        else if (i == 2) {
            postcode = malloc(strlen(buffer) * sizeof(char));
            delete_spaces(buffer, postcode);
            string_to_lower(postcode);
            mentry->postcode = postcode;
            strcat(full_address, buffer);
        }
    }
    mentry->full_address = full_address;
    return mentry;
};

// Prints MEntry in original formatting to fd.
void me_print(MEntry *me, FILE *fd) {
    fprintf(fd, me->full_address);
}