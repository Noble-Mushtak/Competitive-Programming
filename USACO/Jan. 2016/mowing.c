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

typedef long item_type;
typedef long item_length;
typedef struct {
    item_type item;
    bool hasItem;
} item_container;
typedef struct segtree_info {
    item_type answer;
    bool subtreesExist[4];
    item_container lazy;
} segtree_info;
typedef struct segtree {
    segtree_info infos[10000000];
} segtree;
segtree tracker;

static inline item_type segtreeMerge(item_type item1, item_type item2) {
    //Merge items by adding them together
    return item1+item2;
}

static inline void segtreeSingleUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_length start2, item_length end2, item_type updateItem) {
    tree->infos[ind].answer += (end-start+1)*(end2-start2+1)*updateItem;
}

static inline void segtreePropogate(segtree *tree, item_type ind, item_type updateItem) {
    item_length i;
    //Propogate to both childs
    for (i = 0; i < 4; i++) if (tree->infos[ind].subtreesExist[i]) {
        //If there is no lazy update, then initialize the lazy update.
        if (!tree->infos[4*ind+i+1].lazy.hasItem) tree->infos[4*ind+i+1].lazy.item = updateItem, tree->infos[4*ind+i+1].lazy.hasItem = true;
        //Otherwise, merge the two updates together.
        else tree->infos[4*ind+i+1].lazy.item = segtreeMerge(tree->infos[4*ind+i+1].lazy.item, updateItem);
   }
}

static inline void segtreeLazy(segtree *tree, item_type ind, item_length start, item_length end, item_length start2, item_length end2) {
    //If there is a lazy update:
    if (tree->infos[ind].lazy.hasItem) {
        //Update tree->list[ind] with tree->lazy[ind].item.
        segtreeSingleUpdate(tree, ind, start, end, start2, end2, tree->infos[ind].lazy.item);
        //Propogate the update if tree->list[ind] has children.
        if (start != end || start2 != end2) segtreePropogate(tree, ind, tree->infos[ind].lazy.item);
        //Erase this lazy update.
        tree->infos[ind].lazy.hasItem = false;
    }
}
 
void segtreeInit(segtree *tree, item_length ind, item_length start, item_length end, item_length start2, item_length end2) {
    //The midpoint of this interval and the number of spaces needed for a segtree from start to end:
    item_length mid = (start+end)/2, mid2 = (start2+end2)/2, numNeeded;

    tree->infos[ind].answer = 0;
    tree->infos[ind].lazy.hasItem = false;
    //If the left half of this interval is only one element, then set the left child accordingly. Otherwise, traverse the left half of this interval.
    tree->infos[ind].subtreesExist[0] = true;
    ((start == mid) && (start2 == mid2)) ? (tree->infos[4*ind+1].answer = 0) : segtreeInit(tree, 4*ind+1, start, mid, start2, mid2);
    tree->infos[ind].answer = segtreeMerge(tree->infos[ind].answer, tree->infos[4*ind+1].answer);
    if (mid2+1 <= end2) {
        tree->infos[ind].subtreesExist[1] = true;
        ((start == mid) && (mid2+1 == end2)) ? (tree->infos[4*ind+2].answer = 0) : segtreeInit(tree, 4*ind+2, start, mid, mid2+1, end);
        tree->infos[ind].answer = segtreeMerge(tree->infos[ind].answer, tree->infos[4*ind+2].answer);
    } else tree->infos[ind].subtreesExist[1] = false;
    //Do the same thing for the right half of this interval.
    if (mid+1 <= end) {
        tree->infos[ind].subtreesExist[2] = true;
        ((mid+1 == end) && (start2 == mid2)) ? (tree->infos[4*ind+3].answer = 0) : segtreeInit(tree, 4*ind+3, mid+1, end, start2, mid2);
        tree->infos[ind].answer = segtreeMerge(tree->infos[ind].answer, tree->infos[4*ind+3].answer);
    } else tree->infos[ind].subtreesExist[2] = false;
    //Merge the two children to set tree->list[ind].
    if (mid+1 <= end && mid2+1 <= end2) {
        tree->infos[ind].subtreesExist[3] = true;
        ((mid+1 == end) && (mid2+1 == end2)) ? (tree->infos[4*ind+4].answer = 0) : segtreeInit(tree, 4*ind+4, mid+1, end, mid2+1, end2);
        tree->infos[ind].answer = segtreeMerge(tree->infos[ind].answer, tree->infos[4*ind+4].answer);
    } else tree->infos[ind].subtreesExist[3] = false;
}
 
item_container segtreeQuery(segtree *tree, item_length ind, item_length start, item_length end, item_length start2, item_length end2, item_length begInterval, item_length endInterval, item_length begInterval2, item_length endInterval2) {
    //The answer for this interval, the answer for the left half of this interval, and the answer for the right half of this interval:
    item_container answer = { .item = 0, .hasItem = false }, storeAnswer;
    //The midpoint of this interval:
    item_length mid = (start+end)/2, mid2 = (start2+end2)/2, i;
    //Update tree->list[ind] with any lazy updates.
    segtreeLazy(tree, ind, start, end, start2, end2);

    //Return the default invalid answer of no item if the query interval has no intersection with this interval.
    if (begInterval > end || endInterval < start || begInterval2 > end2 || endInterval2 < start2) return answer;
    //If this interval is completely inside the query interval, simply return tree->list[ind]
    if (start >= begInterval && end <= endInterval && start2 >= begInterval2 && end2 <= endInterval2) {
        answer.hasItem = true, answer.item = tree->infos[ind].answer;
        return answer;
    }

    //If none of the cases above apply, traverse both halves of this interval.
    for (i = 0; i < 4; i++) if (tree->infos[ind].subtreesExist[i]) {
        storeAnswer = segtreeQuery(tree, 4*ind+i+1, ((i & 2) ? mid+1 : start), ((i & 2) ? end : mid), ((i & 1) ? mid2+1 : start2), ((i & 1) ? end2 : mid2), begInterval, endInterval, begInterval2, endInterval2);
        if (storeAnswer.hasItem) {
            answer.hasItem = true;
            answer.item = segtreeMerge(answer.item, storeAnswer.item);
        }
    }
    return answer;
}
 
void segtreeUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_length start2, item_length end2, item_length begInterval, item_length endInterval, item_length begInterval2, item_length endInterval2, item_type updateItem) {
    //The midpoint of this interval:
    item_length mid = (start+end)/2, mid2 = (start2+end2)/2, i;
    //Update tree->list[ind] with any lazy updates.
    segtreeLazy(tree, ind, start, end, start2, end2);
    //printf("%li %li %li %li | %li %li %li %li | %hhi %hhi %hhi %hhi | %hhi %hhi %hhi %hhi\n", start, end, start2, end2, begInterval, endInterval, begInterval2, endInterval2, start >= begInterval, end <= endInterval, start2 >= begInterval2, end2 <= endInterval2, begInterval > end, endInterval < start, begInterval2 > end2, endInterval < start2);
    
    //Return if the update interval has no intersection with this interval or ind is outside of the tree.   
    if (begInterval > end || endInterval < start || begInterval2 > end2 || endInterval2 < start2) return;
    //If this interval is completely inside the update interval, update tree->list[ind] with updateItem and propogate if there are children.
    if (start >= begInterval && end <= endInterval && start2 >= begInterval2 && end2 <= endInterval2) {
        segtreeSingleUpdate(tree, ind, start, end, start2, end2, updateItem);
        if (start != end || start2 != end2) segtreePropogate(tree, ind, updateItem);
    }
    //Otherwise, traverse both halves of the interval and update tree->list[ind] by merging the two children.
    else {
        tree->infos[ind].answer = 0;
        for (i = 0; i < 4; i++) if (tree->infos[ind].subtreesExist[i]) {
            segtreeUpdate(tree, 4*ind+i+1, ((i & 2) ? mid+1 : start), ((i & 2) ? end : mid), ((i & 1) ? mid2+1 : start2), ((i & 1) ? end2 : mid2), begInterval, endInterval, begInterval2, endInterval2, updateItem);
            tree->infos[ind].answer = segtreeMerge(tree->infos[ind].answer, tree->infos[4*ind+i+1].answer);
        }
    }
}


typedef long dimen;
typedef long num_points;
typedef long long num_crosses;
typedef long time;
typedef struct {
    dimen x, y;
} point;

FILE *in, *out;
time numDays, growBack;
num_points numXs, numYs;
dimen xs[100000], ys[100000], newXs[100000], newYs[100000], minX, maxX, minY, maxY;
point positions[100000];
num_crosses answer = 0;

dimen binarySearch(dimen coords[100000], num_points numCoords, dimen coord) {
    dimen beg = 0, end = numCoords-1, mid;
    while (beg <= end) {
        mid = (beg+end)/2;
        if (coords[mid] == coord) return mid;
        else if (coords[mid] < coord) beg = mid+1;
        else end = mid-1;
    }
}

int compareDimens(const void *ptr1, const void *ptr2) {
    dimen dimen1 = *(dimen*)ptr1, dimen2 = *(dimen*)ptr2;
    return (dimen1 > dimen2)-(dimen1 < dimen2);
}

int main() {
    time i;
    dimen temp;
    
    in = fopen("mowing.in", "r");
    fscanf(in, "%li %li", &numDays, &growBack);
    REPEAT(i, numDays) {
        fscanf(in, "%li %li", &(positions[i].x), &(positions[i].y));
        xs[i] = positions[i].x, ys[i] = positions[i].y;
    }
    fclose(in);

    qsort(xs, numDays, sizeof(dimen), compareDimens);
    qsort(ys, numDays, sizeof(dimen), compareDimens);
    REPEAT(i, numDays) {
        if (i == 0 || xs[i] > xs[i-1]) newXs[numXs++] = xs[i];
        if (i == 0 || ys[i] > ys[i-1]) newYs[numYs++] = ys[i];
    }
    REPEAT(i, numDays) {
        positions[i].x = binarySearch(newXs, numXs, positions[i].x);
        positions[i].y = binarySearch(newYs, numYs, positions[i].y);
    }

    segtreeInit(&tracker, 0, 0, numXs-1, 0, numYs-1);
    REPEAT(i, numDays-1) {
        if (i >= growBack) {
            minX = positions[i-growBack].x, maxX = positions[i-growBack+1].x;
            if (maxX < minX) temp = maxX, maxX = minX, minX = temp;
            if (minX != maxX) minX++, maxX--;
            minY = positions[i-growBack].y, maxY = positions[i-growBack+1].y;
            if (maxY < minY) temp = maxY, maxY = minY, minY = temp;
            if (minY != maxY) minY++, maxY--;
            //printf("U: %li %li %li %li\n", minX, maxX, minY, maxY);
            segtreeUpdate(&tracker, 0, 0, numXs-1, 0, numYs-1, minX, maxX, minY, maxY, 1);
        }
        minX = positions[i].x, maxX = positions[i+1].x;
        if (maxX < minX) temp = maxX, maxX = minX, minX = temp;
        if (minX != maxX) minX++, maxX--;
        minY = positions[i].y, maxY = positions[i+1].y;
        if (maxY < minY) temp = maxY, maxY = minY, minY = temp;
        if (minY != maxY) minY++, maxY--;
        //printf("Q: %li %li %li %li\n", minX, maxX, minY, maxY);
        answer += (segtreeQuery(&tracker, 0, 0, numXs-1, 0, numYs-1, minX, maxX, minY, maxY)).item;
    }
    
    out = fopen("mowing.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}