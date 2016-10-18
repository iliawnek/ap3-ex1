#include "mentry.h"

int main(int argc, char *argv[]) {
    MEntry *me;
    MEntry *mes[12];
    int i = 0;
    while ((me = me_get(stdin)) != NULL) {
        mes[i++] = me;
        me_print(me, stdout);
        printf("-----------\n");
        printf("Surname: %s\n", me->surname);
        if (me->house_number != 0) {
            printf("House number: %d\n", me->house_number);
        }
        printf("Postcode: %s\n", me->postcode);
        printf("-----------\n");
        printf("%lu\n", me_hash(me, 1000000));
        printf("\n");
        printf("\n");
    };

    printf("%d\n", me_compare(mes[0], mes[10]));
    printf("%d\n", me_compare(mes[1], mes[3]));
    printf("%d\n", me_compare(mes[4], mes[6]));
    printf("%d\n", me_compare(mes[9], mes[11]));
}