#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef signed char byte;
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }

typedef long num_cards;
typedef long card;

FILE *in, *out;
num_cards numCards, numPerPlayer, numPerRound, numPointsFirstRound, numPointsSecondRound, numBessieHas, indexReach[50002];
card bessie[50000], elsie[50000], segtreeBase[100000];
bool elsieHas[100000], bessieUsed[100000];

typedef card item_type;
typedef num_cards item_length;
typedef struct {
    item_type item;
    bool hasItem;
} item_container;
typedef struct segtree {
    item_type list[300000];
    item_container lazy[300000];
    item_length size;
    item_length length;
    item_length intervalMin;
    item_length intervalMax;
} segtree;
segtree segtreeMin, segtreeMax;
bool segtreeIsMin;

static inline item_type segtreeMerge(item_type item1, item_type item2) {
    return (!segtreeIsMin ? (item1 < item2) : (item1 > item2)) ? item1 : item2;
}

static inline void segtreeSingleUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_type updateItem) {
    tree->list[ind] = updateItem;
}

static inline void segtreePropogate(segtree *tree, item_length ind, item_type updateItem) {
    item_length i;
    //Propogate to both childs
    for (i = 0; i < 2; i++) {
        //If there is no lazy update, then initialize the lazy update.
        if (!tree->lazy[2*ind+i+1].hasItem) tree->lazy[2*ind+i+1].item = updateItem, tree->lazy[2*ind+i+1].hasItem = true;
        //Otherwise, merge the two updates together.
        else tree->lazy[2*ind+i+1].item = segtreeMerge(tree->lazy[2*ind+i+1].item, updateItem);
   }
}

static inline void segtreeLazy(segtree *tree, item_length ind, item_length start, item_length end) {
    //If there is a lazy update:
    if (tree->lazy[ind].hasItem) {
        //Update tree->list[ind] with tree->lazy[ind].item.
        segtreeSingleUpdate(tree, ind, start, end, tree->lazy[ind].item);
        //Propogate the update if tree->list[ind] has children.
        if (start != end) segtreePropogate(tree, ind, tree->lazy[ind].item);
        //Erase this lazy update.
        tree->lazy[ind].hasItem = false;
    }
}
 
void segtreeInit(segtree *tree, item_length ind, item_length start, item_length end, item_type *items) {
    //The midpoint of this interval and the number of spaces needed for a segtree from start to end:
    item_length mid = (start+end)/2, numNeeded;

    //If the left half of this interval is only one element, then set the left child accordingly. Otherwise, traverse the left half of this interval.
    (start == mid) ? (tree->list[2*ind+1] = items[start]) : segtreeInit(tree, 2*ind+1, start, mid, items);
    //Do the same thing for the right half of this interval.
    (mid+1 == end) ? (tree->list[2*ind+2] = items[mid+1]) : segtreeInit(tree, 2*ind+2, mid+1, end, items);
    //If tree->length is less than 2*ind+3, set tree->length accordingly.
    if (tree->length < 2*ind+3) tree->length = 2*ind+3;
    //Merge the two children to set tree->list[ind].
    tree->list[ind] = segtreeMerge(tree->list[2*ind+1], tree->list[2*ind+2]);
}
 
item_container segtreeQuery(segtree *tree, item_length ind, item_length start, item_length end, item_length begInterval, item_length endInterval) {
    //The answer for this interval, the answer for the left half of this interval, and the answer for the right half of this interval:
    item_container answer = { .item = 0, .hasItem = false }, ans1, ans2;
    //The midpoint of this interval:
    item_length mid = (start+end)/2;
    //Update tree->list[ind] with any lazy updates.
    segtreeLazy(tree, ind, start, end);

    //Return the default invalid answer of no item if the query interval has no intersection with this interval.
    if (begInterval > end || endInterval < start) return answer;
    //If this interval is completely inside the query interval, simply return tree->list[ind]
    if (start >= begInterval && end <= endInterval) {
        answer.hasItem = true, answer.item = tree->list[ind];
        return answer;
    }

    //If none of the cases above apply, traverse both halves of this interval.
    ans1 = segtreeQuery(tree, 2*ind+1, start, mid, begInterval, endInterval);
    ans2 = segtreeQuery(tree, 2*ind+2, mid+1, end, begInterval, endInterval);
    //If one of the answers is invalid, return the other answer.
    if (!ans1.hasItem) return ans2;
    if (!ans2.hasItem) return ans1;
    //Otherwise, return the merge of the two answers.
    answer.hasItem = true, answer.item = segtreeMerge(ans1.item, ans2.item);
    return answer;
}
 
void segtreeUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_length begInterval, item_length endInterval, item_type updateItem) {
    //The midpoint of this interval:
    item_length mid = (start+end)/2;
    //Update tree->list[ind] with any lazy updates.
    segtreeLazy(tree, ind, start, end);
    
    //Return if the update interval has no intersection with this interval or ind is outside of the tree.   
    if (begInterval > end || endInterval < start) return;
    //If this interval is completely inside the update interval, update tree->list[ind] with updateItem and propogate if there are children.
    if (start >= begInterval && end <= endInterval) {
        segtreeSingleUpdate(tree, ind, start, end, updateItem);
        if (start != end) segtreePropogate(tree, ind, updateItem);
    }
    //Otherwise, traverse both halves of the interval and update tree->list[ind] by merging the two children.
    else {
        segtreeUpdate(tree, 2*ind+1, start, mid, begInterval, endInterval, updateItem);
        segtreeUpdate(tree, 2*ind+2, mid+1, end, begInterval, endInterval, updateItem);
        tree->list[ind] = segtreeMerge(tree->list[2*ind+1], tree->list[2*ind+2]);
    }
}

int main() {
    char store;
    num_cards i, curIndex, updateIndex;
    card j;
    
    in = fopen("cardgame.in", "r");
    fscanf(in, "%li", &numPerPlayer);
    numCards = numPerPlayer*2, numPerRound = numPerPlayer/2;
    REPEAT(i, numPerPlayer) fscanf(in, "%li", elsie+i), elsie[i]--, elsieHas[elsie[i]] = true;
    fclose(in);

    REPEAT(j, numCards) if (!elsieHas[j]) bessie[numBessieHas++] = j;
    inline int compareCards(const void *ptr1, const void *ptr2) {
        card card1 = *(card*)ptr1, card2 = *(card*)ptr2;
        return (card1 > card2)-(card1 < card2);
    }
    qsort(elsie, numPerRound, sizeof(card), compareCards);
    qsort(elsie+numPerRound, numPerRound, sizeof(card), compareCards);

    curIndex = -1;
    REPEAT(i, numCards) {
        if (curIndex+1 < numPerRound && i > elsie[curIndex+1]) indexReach[curIndex+1] = i-1, curIndex++;
        segtreeBase[i] = curIndex; 
    }
    indexReach[curIndex+1] = numCards-1;
    segtreeIsMin = false;
    segtreeInit(&segtreeMax, 0, 0, numCards-1, segtreeBase);
    REPEAT(i, numPerPlayer) {
        curIndex = (segtreeQuery(&segtreeMax, 0, 0, numCards-1, bessie[numPerPlayer-i-1], bessie[numPerPlayer-i-1])).item;
        //printf("F %li %li\n", bessie[numPerPlayer-i-1], curIndex);
        if (curIndex > -1) {
            numPointsFirstRound++;
            updateIndex = (segtreeQuery(&segtreeMax, 0, 0, numCards-1, elsie[curIndex], elsie[curIndex])).item;
            segtreeUpdate(&segtreeMax, 0, 0, numCards-1, elsie[curIndex]+1, indexReach[curIndex+1], updateIndex);
            //printf("%li %li\n", elsie[curIndex]+1, indexReach[curIndex+1]);
            indexReach[updateIndex+1] = indexReach[curIndex+1];
        }
    }

    curIndex = numPerPlayer;
    for (i = numCards-1; i >= 0; i--) {
        if (curIndex-1 >= numPerRound && i < elsie[curIndex-1]) indexReach[curIndex+1] = i+1, curIndex--;
        segtreeBase[i] = curIndex;
    }
    indexReach[curIndex+1] = 0;
    segtreeIsMin = true;
    segtreeInit(&segtreeMin, 0, 0, numCards-1, segtreeBase);
    REPEAT(i, numPerPlayer) {
        curIndex = (segtreeQuery(&segtreeMin, 0, 0, numCards-1, bessie[i], bessie[i])).item;
        //printf("S %li %li\n", bessie[i], curIndex);
        if (curIndex < numPerPlayer) {
            numPointsSecondRound++;
            updateIndex = (segtreeQuery(&segtreeMin, 0, 0, numCards-1, elsie[curIndex], elsie[curIndex])).item;
            segtreeUpdate(&segtreeMin, 0, 0, numCards-1, indexReach[curIndex+1], elsie[curIndex]-1, updateIndex);
            indexReach[updateIndex+1] = indexReach[curIndex+1];
        }
    }
    
    out = fopen("cardgame.out", "w");
    fprintf(out, "%li\n", numPointsFirstRound+numPointsSecondRound);
    fclose(out);
    
    exit(0);
}