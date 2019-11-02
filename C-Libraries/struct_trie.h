/**
 * struct trie (and others) for C
 * Documentation coming soon!
*/

typedef struct trie {
    struct trie *bit0;
    struct trie *bit1;
} trie;
trie space[1000000], start;
num_bits nextSpace;

void insert(trie *trie, num query) {
    num_bits bitsLeft;
    for (bitsLeft = 21; bitsLeft > 0; bitsLeft--) {
        if (query & (1 << (bitsLeft-1))) {
            if (trie->bit1 == NULL) {
                trie->bit1 = space+(nextSpace++);
                if (nextSpace >= 1000000) puts("NO!"), exit(1);
            }
            trie = trie->bit1;
        } else {
            if (trie->bit0 == NULL) {
                trie->bit0 = space+(nextSpace++);
                if (nextSpace >= 1000000) puts("NO!"), exit(1);
            }
            trie = trie->bit0;
        }
    }
}

num findClosest(trie *trie, num query) {
    num_bits bitsLeft;
    num answer = 0;
    for (bitsLeft = 21; bitsLeft > 0; bitsLeft--) {
        if ((query & (1 << (bitsLeft-1)) && trie->bit1 != NULL) || trie->bit0 == NULL) answer += (1 << (bitsLeft-1)), trie = trie->bit1;
        else trie = trie->bit0;
    }
    return answer;
}