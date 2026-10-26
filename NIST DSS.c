#include stdio.h
#include string.h

long long power(long long a, long long b, long long p)
{
    long long r = 1;
    while (b  0)
    {
        r = (r  a) % p;
        b--;
    }
    return r;
}

long long inverse(long long a, long long m)
{
    long long i;
    for (i = 1; i  m; i++)
        if ((a  i) % m == 1)
            return i;
    return -1;
}

long long hash(char msg[])
{
    long long h = 0;
    int i;

    for (i = 0; msg[i] != '0'; i++)
        h = (h  31 + (unsigned char)msg[i]) % 11;

    return h;
}

int verify(char msg[], long long r, long long s,
           long long p, long long q, long long g, long long y)
{
    long long h = hash(msg);
    long long w = inverse(s, q);
    long long u1 = (h  w) % q;
    long long u2 = (r  w) % q;
    long long v = (power(g, u1, p)  power(y, u2, p) % p) % q;

    printf(Hash value = %lldn, h);
    printf(w = %lldn, w);
    printf(u1 = %lldn, u1);
    printf(u2 = %lldn, u2);
    printf(v = %lldn, v);

    return v == r;
}

int main()
{
    long long p = 23, q = 11, g = 4;
    long long x = 3, y, k, r, s, h;
    char msg[200], modified[220];

    printf(Enter message );
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, n)] = '0';

    y = power(g, x, p);
    h = hash(msg);

    for (k = 1; k  q; k++)
    {
        r = power(g, k, p) % q;

        if (r == 0)
            continue;

        s = (inverse(k, q)  (h + x  r)) % q;

        if (s != 0)
            break;
    }

    if (k == q)
    {
        printf(Could not generate signature.n);
        return 1;
    }

    printf(n--- DSA Signing ---n);
    printf(Message = %sn, msg);
    printf(p = %lldn, p);
    printf(q = %lldn, q);
    printf(g = %lldn, g);
    printf(Private key x = %lldn, x);
    printf(Public key y = %lldn, y);
    printf(Hash value = %lldn, h);
    printf(Random nonce k = %lldn, k);
    printf(Signature r = %lldn, r);
    printf(Signature s = %lldn, s);

    printf(n--- DSA Verification ---n);

    if (verify(msg, r, s, p, q, g, y))
        printf(Signature is VALIDn);
    else
        printf(Signature is INVALIDn);

    strcpy(modified, msg);
    strcat(modified, X);

    printf(nModified message = %sn, modified);
    printf(--- Modified Message Verification ---n);

    if (verify(modified, r, s, p, q, g, y))
        printf(Signature is VALIDn);
    else
        printf(Signature is INVALIDn);

    return 0;
}
