#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[]){
    int used[26]={0};
    int r=0,c=0;

    used['J'-'A']=1;

    for(int i=0;key[i]!='\0';i++){
        char ch=toupper((unsigned char)key[i]);

        if(!isalpha((unsigned char)ch))
            continue;

        if(ch=='J')
            ch='I';

        if(!used[ch-'A']){
            matrix[r][c]=ch;
            used[ch-'A']=1;
            c++;

            if(c==5){
                c=0;
                r++;
            }
        }
    }

    for(char ch='A';ch<='Z';ch++){
        if(ch=='J')
            continue;

        if(!used[ch-'A']){
            matrix[r][c]=ch;
            used[ch-'A']=1;
            c++;

            if(c==5){
                c=0;
                r++;
            }
        }
    }
}

void findPosition(char ch,int *r,int *c){
    if(ch=='J')
        ch='I';

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(matrix[i][j]==ch){
                *r=i;
                *c=j;
                return;
            }
        }
    }
}

void prepareText(char input[],char output[]){
    char letters[500];
    int n=0;

    for(int i=0;input[i]!='\0';i++){
        if(isalpha((unsigned char)input[i])){
            char ch=toupper((unsigned char)input[i]);

            if(ch=='J')
                ch='I';

            letters[n++]=ch;
        }
    }

    letters[n]='\0';

    int k=0;

    for(int i=0;i<n;){
        output[k++]=letters[i];

        if(i+1<n){
            if(letters[i]==letters[i+1]){
                output[k++]='X';
                i++;
            }
            else{
                output[k++]=letters[i+1];
                i+=2;
            }
        }
        else{
            output[k++]='X';
            i++;
        }
    }

    output[k]='\0';
}

void encryptPair(char a,char b,char *x,char *y){
    int r1,c1,r2,c2;

    findPosition(a,&r1,&c1);
    findPosition(b,&r2,&c2);

    if(r1==r2){
        *x=matrix[r1][(c1+1)%5];
        *y=matrix[r2][(c2+1)%5];
    }
    else if(c1==c2){
        *x=matrix[(r1+1)%5][c1];
        *y=matrix[(r2+1)%5][c2];
    }
    else{
        *x=matrix[r1][c2];
        *y=matrix[r2][c1];
    }
}

void encrypt(char text[]){
    char letters[500];
    char encrypted[500];
    int positions[500];
    int n=0;

    for(int i=0;text[i]!='\0';i++){
        if(isalpha((unsigned char)text[i])){
            letters[n]=toupper((unsigned char)text[i]);
            positions[n]=i;
            n++;
        }
    }

    char prepared[1000];
    prepareText(text,prepared);

    int p=0;

    for(int i=0;i<(int)strlen(prepared);i+=2){
        char a,b;

        encryptPair(prepared[i],prepared[i+1],&a,&b);

        encrypted[p++]=a;
        encrypted[p++]=b;
    }

    int encryptedIndex=0;

    printf("Encrypted Text: ");

    for(int i=0;text[i]!='\0';i++){
        if(isalpha((unsigned char)text[i])){
            if(encryptedIndex<p)
                printf("%c",encrypted[encryptedIndex++]);
        }
        else{
            printf("%c",text[i]);
        }
    }

    printf("\n");
}

int main(){
    char key[100];
    char plaintext[500];

    printf("Enter key: ");
    fgets(key,sizeof(key),stdin);
    key[strcspn(key,"\n")]='\0';

    printf("Enter plaintext: ");
    fgets(plaintext,sizeof(plaintext),stdin);
    plaintext[strcspn(plaintext,"\n")]='\0';

    createMatrix(key);

    printf("\nPlayfair Matrix:\n");

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            printf("%c ",matrix[i][j]);
        printf("\n");
    }

    encrypt(plaintext);

    return 0;
}