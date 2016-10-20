#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *surnames[] = {
        "Watts",
        "Smith",
        "Jones",
        "Taylor",
        "Williams",
        "Brown",
        "Davies",
        "Evans",
        "Wilson",
        "Thomas",
        "Roberts",
        "Johnson",
        "Lewis",
        "Walker",
        "Robinson",
        "Wood",
        "Thompson",
        "White",
        "Watson",
        "Jackson",
        "Wright",
        "Green",
        "Harris",
        "Cooper",
//            "King",
//            "Lee",
//            "Martin",
//            "Clarke",
//            "James",
//            "Morgan",
//            "Hughes",
//            "Edwards",
//            "Hill",
//            "Moore",
//            "Clark",
//            "Harrison",
//            "Scott",
//            "Young",
//            "Morris",
//            "Hall",
//            "Ward",
//            "Turner",
//            "Carter",
//            "Phillips",
//            "Mitchell",
//            "Patel",
//            "Adams",
//            "Campbell",
//            "Anderson",
//            "Allen",
//            "Cook",
//            "Bailey",
//            "Parker",
//            "Miller",
//            "Davis",
//            "Murphy",
//            "Price",
//            "Bell",
//            "Baker",
//            "Griffiths",
//            "Kelly",
//            "Simpson",
//            "Marshall",
//            "Collins",
//            "Bennett",
//            "Cox",
//            "Richardson",
//            "Fox",
//            "Gray",
//            "Rose",
//            "Chapman",
//            "Hunt",
//            "Robertson",
//            "Shaw",
//            "Reynolds",
//            "Lloyd",
//            "Ellis",
//            "Richards",
//            "Russell",
//            "Wilkinson",
//            "Khan",
//            "Graham",
//            "Stewart",
//            "Reid",
//            "Murray",
//            "Powell",
//            "Palmer",
//            "Holmes",
//            "Rogers",
//            "Stevens",
//            "Walsh",
//            "Hunter",
//            "Thomson",
//            "Matthews",
//            "Ross",
//            "Owen",
//            "Mason",
//            "Knight",
//            "Kennedy",
//            "Butler",
//            "Saunders",
//            "Cole",
//            "Pearce",
//            "Dean",
//            "Foster",
//            "Harvey",
//            "Hudson",
//            "Gibson",
//            "Mills",
//            "Berry",
//            "Barnes",
//            "Pearson",
//            "Kaur",
//            "Booth",
//            "Dixon",
//            "Grant",
//            "Gordon",
//            "Lane",
//            "Harper",
//            "Ali",
//            "Hart",
//            "Mcdonald",
//            "Brooks",
//            "Ryan",
//            "Carr",
//            "Macdonald",
//            "Hamilton",
//            "Johnston",
//            "West",
//            "Gill",
//            "Dawson",
//            "Armstrong",
//            "Gardner",
//            "Stone",
//            "Andrews",
//            "Williamson",
//            "Barker",
//            "George",
//            "Fisher",
//            "Cunningham",
//            "Watts",
//            "Webb",
//            "Lawrence",
//            "Bradley",
//            "Jenkins",
//            "Wells",
//            "Chambers",
//            "Spencer",
//            "Poole",
//            "Atkinson",
//            "Lawson"
};

char letters[] = {'A', 'B', 'C'};

char get_random_letter() {
    return letters[rand() % 3];
}

int get_random_number() {
    return 1 + rand() % 10 + 1;
}

char *get_random_postcode() {
    char *postcode = malloc(7 * sizeof(char));
    postcode[0] = get_random_letter();
    itoa(get_random_number(), &postcode[1], 10);
    postcode[2] = get_random_letter();
    postcode[3] = ' ';
    postcode[4] = get_random_letter();
    itoa(get_random_number(), &postcode[5], 10);
    postcode[6] = get_random_letter();
    return postcode;
}

//char **read_surnames(FILE *file, int number_of_surnames) {
//    char **surnames = malloc(sizeof(char) * number_of_surnames * 10);
//    char buffer[10];
//    int index = 0;
//    while ((fgets(buffer, 10, file)) != NULL) {
//        strcpy(surnames[index], buffer);
//        index++;
//    }
//    return surnames;
//}

char *get_random_surname(char **surnames, int number_of_surnames) {
    return surnames[rand() % (number_of_surnames - 1)];
}

int main(int argc, char *argv[]) {
    if (argc != 2) return -1;
    for (int i = 0; i < atoi(argv[1]); i++) {
        printf("%s, %s\n", get_random_surname(surnames, 10), get_random_surname(surnames, 10));
        printf("%d\n", get_random_number());
        printf("%s\n", get_random_postcode());
//        printf("\n");
    }
}