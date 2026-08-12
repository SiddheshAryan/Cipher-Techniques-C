#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

int mod(int x,int m){
    x%=m;
    if(x<0)x+=m;
    return x;
}

int determinant(int key[SIZE][SIZE]){
    return key[0][0]*key[1][1]-key[0][1]*key[1][0];
}

int modInverse(int a,int m){
    a=mod(a,m);
    for(int i=1;i<m;i++){
        if((a*i)%m==1)
            return i;
    }
    return -1;
}

void encrypt(char text[],int key[SIZE][SIZE]){
    int len=strlen(text);
    char letters[500];
    int letterCount=0;

    for(int i=0;i<len;i++){
        if(isalpha((unsigned char)text[i]))
            letters[letterCount++]=toupper((unsigned char)text[i]);
    }

    int originalCount=letterCount;

    if(letterCount%2!=0)
        letters[letterCount++]='X';

    for(int i=0;i<letterCount;i+=2){
        int x1=letters[i]-'A';
        int x2=letters[i+1]-'A';

        int y1=mod(key[0][0]*x1+key[0][1]*x2,26);
        int y2=mod(key[1][0]*x1+key[1][1]*x2,26);

        letters[i]=y1+'A';
        letters[i+1]=y2+'A';
    }

    int letterIndex=0;

    printf("Encrypted Text: ");

    for(int i=0;i<len;i++){
        if(isalpha((unsigned char)text[i])){
            if(letterIndex<originalCount)
                printf("%c",letters[letterIndex++]);
        }
        else{
            printf("%c",text[i]);
        }
    }

    printf("\n");
}

int main(){
    char text[500];
    int key[SIZE][SIZE];

    printf("Enter plaintext: ");
    fgets(text,sizeof(text),stdin);
    text[strcspn(text,"\n")]='\0';

    printf("Enter 2x2 key matrix:\n");

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++)
            scanf("%d",&key[i][j]);
    }

    int det=determinant(key);
    int inverse=modInverse(det,26);

    if(inverse==-1){
        printf("Invalid key! Matrix has no inverse modulo 26.\n");
        return 1;
    }

    encrypt(text,key);

    return 0;
}