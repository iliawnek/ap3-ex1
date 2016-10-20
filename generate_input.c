#include <stdio.h>
#include <stdlib.h>

char *surnames[] = {"Watts", "Smith", "Jones", "Taylor", "Williams", "Brown", "Davies", "Evans", "Wilson", "Thomas", "Roberts", "Johnson", "Lewis", "Walker", "Robinson", "Wood", "Thompson", "White", "Watson", "Jackson", "Wright", "Green", "Harris", "Cooper", "King", "Lee", "Martin", "Clarke", "James", "Morgan", "Hughes", "Edwards", "Hill", "Moore", "Clark", "Harrison", "Scott", "Young", "Morris", "Hall", "Ward", "Turner", "Carter", "Phillips", "Mitchell", "Patel", "Adams", "Campbell", "Anderson", "Allen", "Cook", "Bailey", "Parker", "Miller", "Davis", "Murphy", "Price", "Bell", "Baker", "Griffiths", "Kelly", "Simpson", "Marshall", "Collins", "Bennett", "Cox", "Richardson", "Fox", "Gray", "Rose", "Chapman", "Hunt", "Robertson", "Shaw", "Reynolds", "Lloyd", "Ellis", "Richards", "Russell", "Wilkinson", "Khan", "Graham", "Stewart", "Reid", "Murray", "Powell", "Palmer", "Holmes", "Rogers", "Stevens", "Walsh", "Hunter", "Thomson", "Matthews", "Ross", "Owen", "Mason", "Knight", "Kennedy", "Butler", "Saunders", "Cole", "Pearce", "Dean", "Foster", "Harvey", "Hudson", "Gibson", "Mills", "Berry", "Barnes", "Pearson", "Kaur", "Booth", "Dixon", "Grant", "Gordon", "Lane", "Harper", "Ali", "Hart", "Mcdonald", "Brooks", "Ryan", "Carr", "Macdonald", "Hamilton", "Johnston", "West", "Gill", "Dawson", "Armstrong", "Gardner", "Stone", "Andrews", "Williamson", "Barker", "George", "Fisher", "Cunningham", "Watts", "Webb", "Lawrence", "Bradley", "Jenkins", "Wells", "Chambers", "Spencer", "Poole", "Atkinson", "Lawson"};
char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char get_random_letter(int unique_letters) {
    return letters[rand() % (unique_letters - 1)];
}

int get_random_number(int unique_numbers) {
    return 1 + rand() % unique_numbers;
}

char *get_random_postcode(int unique_letters, int unique_numbers) {
    char *postcode = malloc(7 * sizeof(char));
    postcode[0] = get_random_letter(unique_letters);
    itoa(get_random_number(unique_numbers), &postcode[1], 10);
    postcode[2] = get_random_letter(unique_letters);
    postcode[3] = ' ';
    postcode[4] = get_random_letter(unique_letters);
    itoa(get_random_number(unique_numbers), &postcode[5], 10);
    postcode[6] = get_random_letter(unique_letters);
    return postcode;
}

char *get_random_surname(char **surnames, int unique_surnames) {
    return surnames[rand() % (unique_surnames - 1)];
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Usage: generate_input\n");
        printf("\t [number of mailing list entries]\n");
        printf("\t [number of unique surnames (max 150)]\n");
        printf("\t [number of unique house numbers]\n");
        printf("\t [number of unique postcode letters (max 26)]\n");
        printf("\t [number of unique postcode digits]\n");
        printf("\t > file.txt");
        return -1;
    }
    for (int i = 0; i < atoi(argv[1]); i++) {
        printf("%s, %s\n", get_random_surname(surnames, atoi(argv[2])), get_random_surname(surnames, atoi(argv[2])));
        printf("%d\n", get_random_number(atoi(argv[3])));
        char *postcode = get_random_postcode(atoi(argv[4]), atoi(argv[5]));
        printf("%s\n", postcode);
        free(postcode);
//        printf("\n");
    }
}