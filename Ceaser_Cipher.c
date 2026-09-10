#include <stdio.h>
#include <ctype.h>

int main() {
    char s[100];
    int key, choice, i;

    printf("Enter message: ");
    fgets(s, 100, stdin);

    printf("Enter key: ");
    scanf("%d", &key);

    printf("1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    if(choice == 2)
        key = -key;

    for(i = 0; s[i] != '\0'; i++) {
        if(isalpha(s[i])) {
            char base = isupper(s[i]) ? 'A' : 'a';
            s[i] = (s[i] - base + key + 26) % 26 + base;
        }
    }

    printf("Result: %s", s);
    return 0;
}






