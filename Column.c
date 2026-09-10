#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trans(char *s, char *key, int dec) {
    char a[200], b[200];
    int n=strlen(key), len=strlen(s), i,j,k=0,col;
    
    if(!dec) {
        for(i=0;i<n;i++) {
            col=0;
            for(j=0;j<n;j++)
                if(key[j]<key[col]) col=j;
            key[col]='{';
            for(j=col;j<len;j+=n) a[k++]=s[j];
        }
        a[k]='\0';
    } else {
        int rows=(len+n-1)/n, p=0;
        for(i=0;i<n;i++) {
            col=0;
            for(j=0;j<n;j++)
                if(key[j]<key[col]) col=j;
            key[col]='{';
            for(j=col;j<len;j+=n) s[j]=a[p++];
        }
        for(i=0;i<len;i++) a[i]=s[i];
        a[len]='\0';
    }
    strcpy(s,a);
}

int main() {
    char text[200],key1[30],key2[30],a[200];
    int choice,i,k=0;

    printf("Enter message: ");
    fgets(text,200,stdin);

    printf("Enter key 1: ");
    scanf("%s",key1);
    printf("Enter key 2: ");
    scanf("%s",key2);

    printf("1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d",&choice);

    if(choice!=1 && choice!=2) {
        printf("Invalid choice!");
        return 0;
    }

    for(i=0;text[i];i++)
        if(isalpha(text[i])) a[k++]=text[i];
    a[k]='\0';

    if(choice==1) {
        trans(a,key1,0);
        trans(a,key2,0);
    } else {
        trans(a,key2,1);
        trans(a,key1,1);
    }

    k=0;
    for(i=0;text[i];i++)
        if(isalpha(text[i])) text[i]=a[k++];

    printf("Result: %s",text);
    return 0;
}