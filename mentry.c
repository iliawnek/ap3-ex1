#include "mentry.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024 // todo: should this be the limit for everything?
#define LINES_PER_ENTRY 3

// todo: source 2
void delete_spaces(char source[], char destination[]) {
    // source is supposed to be zero ended
    // destination is supposed to be large enough to hold source
    int d = 0;
    for (int s = 0; source[s] != '\0'; s++)
        if (source[s] != ' ') {
            destination[d] = source[s];
            d++;
        }
    destination[d] = '\0';
}

void string_to_lower(char source[]) {
    for (int s = 0; source[s] != '\0'; s++) {
        source[s] = (char) tolower(source[s]);
    }
}

MEntry *me_get(FILE *fd) {
    // allocate space in memory for new MEntry
    MEntry *me = malloc(sizeof(MEntry));
    char *surname;
    int *house_number = malloc(sizeof(int));
    char *postcode;
    char full_address[BUFFER_SIZE];

    // read file
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < LINES_PER_ENTRY; i++) {
        if (fgets(buffer, BUFFER_SIZE, fd) == NULL) {
            // todo: deallocate current MEntry from memory
            return NULL;
        }
        if (i == 0) {
            surname = malloc(strlen(buffer) * sizeof(char));
            sscanf(buffer, "%[^,]", surname); // todo: source 1
            string_to_lower(surname);
            printf("%s\n", surname);
        } else if (i == 1) {
            sscanf(buffer, "%d", house_number);
            printf("%d\n", *house_number);
        } else if (i == 2) {
            postcode = malloc(strlen(buffer) * sizeof(char));
            delete_spaces(buffer, postcode);
            string_to_lower(postcode);
            printf("%s\n", postcode);
        }
    }
    return me;
};