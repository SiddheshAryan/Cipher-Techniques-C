#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[],char key[]){
    int keyIndex=0;
    int keyLength=strlen(key);

    for(int i=0;text[i]!='\0';i++){
        if(isalpha((unsigned char)text[i])){
            char k=toupper((unsigned char)key[keyIndex%keyLength]);
            int shift=k-'A';

            if(isupper((unsigned char)text[i]))
                text[i]=((text[i]-'A'+shift)%26)+'A';
            else
                text[i]=((text[i]-'a'+shift)%26)+'a';

            keyIndex++;
        }
    }
}

int main(){
    char text[500];
    char key[100];

    printf("Enter plaintext: ");
    fgets(text,sizeof(text),stdin);
    text[strcspn(text,"\n")]='\0';

    printf("Enter key: ");
    fgets(key,sizeof(key),stdin);
    key[strcspn(key,"\n")]='\0';

    int valid=0;

    for(int i=0;key[i]!='\0';i++){
        if(isalpha((unsigned char)key[i])){
            valid=1;
            break;
        }
    }

    if(!valid){
        printf("Invalid key!\n");
        return 1;
    }

    encrypt(text,key);

    printf("Encrypted Text: %s\n",text);

    return 0;
}



