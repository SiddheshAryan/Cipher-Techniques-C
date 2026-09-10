#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100], letters[100], result[100];
    int rail[100], n, choice, i, r = 0, d = 1, k = 0, p = 0;

    printf("Enter message: ");
    fgets(text, 100, stdin);

    printf("Enter rails: ");
    scanf("%d", &n);

    printf("1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    if(n < 2 || n > 10 || (choice != 1 && choice != 2)) {
        printf("Invalid input!");
        return 0;
    }

    for(i = 0; text[i]; i++)
        if(isalpha(text[i]))
            letters[k++] = text[i];

    letters[k] = '\0';

    for(i = 0; i < k; i++) {
        rail[i] = r;
        if(r == 0) d = 1;
        if(r == n - 1) d = -1;
        r += d;
    }

    if(choice == 1) {
        for(r = 0; r < n; r++)
            for(i = 0; i < k; i++)
                if(rail[i] == r)
                    result[p++] = letters[i];
    } else {
        for(r = 0; r < n; r++)
            for(i = 0; i < k; i++)
                if(rail[i] == r)
                    letters[i] = text[p++];
        
        for(i = 0; i < k; i++)
            result[i] = letters[i];
    }

    result[k] = '\0';

    p = 0;
    for(i = 0; text[i]; i++)
        if(isalpha(text[i]))
            text[i] = result[p++];

    printf("Result: %s", text);

    return 0;
}