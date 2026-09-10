#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && used[ch - 'A'] == 0) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (used[ch - 'A'] == 0) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}

void findPosition(char ch, int *r, int *c) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void process(char text[], char result[], int decrypt) {
    int i, r1, c1, r2, c2;
    char a, b;

    for (i = 0; text[i] != '\0'; i += 2) {
        a = text[i];
        b = text[i + 1];

        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);

        if (r1 == r2) {
            if (decrypt) {
                result[i] = matrix[r1][(c1 + 4) % 5];
                result[i + 1] = matrix[r2][(c2 + 4) % 5];
            } else {
                result[i] = matrix[r1][(c1 + 1) % 5];
                result[i + 1] = matrix[r2][(c2 + 1) % 5];
            }
        }
        else if (c1 == c2) {
            if (decrypt) {
                result[i] = matrix[(r1 + 4) % 5][c1];
                result[i + 1] = matrix[(r2 + 4) % 5][c2];
            } else {
                result[i] = matrix[(r1 + 1) % 5][c1];
                result[i + 1] = matrix[(r2 + 1) % 5][c2];
            }
        }
        else {
            result[i] = matrix[r1][c2];
            result[i + 1] = matrix[r2][c1];
        }
    }

    result[i] = '\0';
}

void prepareText(char text[], char prepared[]) {
    int i, j = 0;
    char ch;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            ch = toupper(text[i]);

            if (ch == 'J')
                ch = 'I';

            if (j > 0 && prepared[j - 1] == ch) {
                prepared[j++] = 'X';
            }

            prepared[j++] = ch;
        }
    }

    if (j % 2 != 0)
        prepared[j++] = 'X';

    prepared[j] = '\0';
}

int main() {
    char key[100], text[100], prepared[200], result[200];
    int choice, i, j;

    printf("Enter key: ");
    scanf("%s", key);

    createMatrix(key);

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    getchar();

    printf("\nEnter message: ");
    fgets(text, 100, stdin);

    printf("\n1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        prepareText(text, prepared);
        process(prepared, result, 0);
        printf("\nEncrypted text: %s\n", result);
    }
    else if (choice == 2) {
        prepareText(text, prepared);
        process(prepared, result, 1);
        printf("\nDecrypted text: %s\n", result);
    }

    return 0;
}