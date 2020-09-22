from __future__ import print_function
import sys

MOD = 1000000007
def next_hash(h, transaction, desired_hash):
    for c in transaction:
        h = (h * 31 + ord(c)) % MOD
    return (desired_hash-h*7) % MOD

needed_hash = 10**7
old_hash = int(sys.stdin.read().split("\n")[0])
tr1 = "charlie-pays-to-eve-9-sg-coins"
tr2 = "icpc-sg-2018-at-nus"
d1 = 930000000
d2 = 730000000
hash1 = next_hash(old_hash, tr1, d1)
hash2 = next_hash(d1, tr2, d2)
print(tr1, hash1)
print(tr2, hash2)