from math import gcd
from hashlib import sha256

p = int(input("Enter prime p: "))
g = int(input("Enter generator g: "))
x = int(input("Enter private key x: "))
y = pow(g, x, p)

def H(m):
    return int(sha256(m.encode()).hexdigest(), 16)

def sign(m):
    h = H(m)
    k = 2
    while (gcd(k, p-1) != 1):
        k += 1
    r = pow(g, k, p)
    s = (pow(k, -1, p - 1) * (h - x * r)) % (p - 1)
    return r, s

def verify(m, r, s):
    if not (1 <= r < p and 0 <= s < p - 1):
        return False
    if gcd(r, p) != 1:
        return False
    return pow(g, H(m), p) == (
        pow(y, r, p) * pow(r, s, p)
    ) % p

n = int(input("Number of messages: "))

for i in range(n):
    m = input(f"\nEnter message {i+1}: ")
    r, s = sign(m)
    print("Signature:", r, s)
    print("Verification:", verify(m, r, s))