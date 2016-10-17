#include "mentry.h"

int main(int argc, char *argv[]) {
    MEntry *me;
    while ((me = me_get(stdin)) != NULL) {
        me_print(me, stdout);
        printf("-----------\n");
        printf("Surname: %s\n", me->surname);
        if (me->house_number != 0) {
            printf("House number: %d\n", me->house_number);
        }
        printf("Postcode: %s\n", me->postcode);
        printf("\n");
    };
}