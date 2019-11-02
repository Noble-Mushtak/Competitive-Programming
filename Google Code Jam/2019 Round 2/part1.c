#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef struct {
    long long arr[400][2];
} item_key;
typedef long long item_value;
typedef long long num_items;

int compareKeys(item_key key1, item_key key2) {
    long long i;
    REPEAT(i, 400) {
        if (key1.arr[i][0] != key2.arr[i][0]) return key1.arr[i][0]-key2.arr[i][0];
        if (key1.arr[i][1] != key2.arr[i][1]) return key1.arr[i][1]-key2.arr[i][1];
    }
    return 0;
}

struct treap {
    item_key key;
    item_value value;
    item_value sum;
    num_items priority;
    num_items size;
    struct treap *left;
    struct treap *right;
};
struct treap_pair {
    struct treap *left;
    struct treap *right;
};

struct treap space[100000];
struct treap *allOrders;
num_items numSpaceUsed;

num_items getTreapSize(struct treap *treap1) {
    if (treap1 == NULL) return 0;
    return treap1->size;
}

item_value getTreapSum(struct treap *treap1) {
    if (treap1 == NULL) return 0;
    return treap1->sum;
}

void calcTreapProperties(struct treap *treap1) {
    if (treap1 != NULL) {
        treap1->size = 1+getTreapSize(treap1->left)+getTreapSize(treap1->right);
        treap1->sum = treap1->value+getTreapSum(treap1->left)+getTreapSum(treap1->right);
    }
}

struct treap *newTreap(item_key key, item_value value) {
    if (numSpaceUsed > 100000) fprintf(stderr, "Ran out of treap space"), exit(1);
    space[numSpaceUsed].priority = rand();
    space[numSpaceUsed].key = key;
    space[numSpaceUsed].value = value;
    space[numSpaceUsed].left = NULL;
    space[numSpaceUsed].right = NULL;
    calcTreapProperties(space+numSpaceUsed);
    numSpaceUsed++;
    return space+(numSpaceUsed-1);
}

struct treap *mergeTreaps(struct treap *left, struct treap *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    if (left->priority > right->priority) {
        left->right = mergeTreaps(left->right, right);
        calcTreapProperties(left);
        return left;
    } else {
        right->left = mergeTreaps(left, right->left);
        calcTreapProperties(right);
        return right;
    }
}

//Split treap into a left-side with all elements less than or equal to key and a right-side with the rest of the elements.
//Note that if exclusive is true, then left-side will have all elements less than key and right-side will have all elements greater than or equal to key.
struct treap_pair splitByKey(struct treap *treap1, item_key key, bool exclusive) {
    struct treap_pair answer;
    if (treap1 == NULL) {
        answer.left = answer.right = NULL;
        return answer;
    }
    
    int compareKeysResult = compareKeys(key, treap1->key);
    //If the key is less than the key of the root, then all items less than or equal to key are on the left-hand side.
    if (exclusive ? (compareKeysResult <= 0) : (compareKeysResult < 0)) {
        answer = splitByKey(treap1->left, key, exclusive);
        //Since answer.left is the tree rooted at key, make answer.right, which has all elements greater than key but less than the key of the root, the new left node of the treap:
        treap1->left = answer.right;
        //After making this modification, treap1 becomes the right-side, which has all elements greater than key:
        answer.right = treap1;
    }
    //If the key is greater than or equal to the key of the root, then we know that the left-side and the root is composed of all elements less than or equal to key, so we need to search the right-hand side for any other elements which are less than or equal to key.
    else {
        answer = splitByKey(treap1->right, key, exclusive);
        //Now, we need to combine treap1 and its left-side with all of the elements in the right-side which are also less than or equal to key.
        //These elements are now in answer.left, so make answer.left the new right-side of treap:
        treap1->right = answer.left;
        //After making this modification, treap1 becomes the left-side, which has all elements less than or equal to key:
        answer.left = treap1;
    }
    calcTreapProperties(treap1);
    return answer;
}

item_value getKeyRangeSum(struct treap **treapPtr, item_key startKey, item_key endKey) {
    //Split the treap up into a left-side which has all elements up to endKey:
    struct treap_pair parts = splitByKey(*treapPtr, endKey, false);
    //Split that treap up into a left-side which has all elements up to startKey-1:
    struct treap_pair parts2 = splitByKey(parts.left, startKey, true);
    //Get the sum of the elements greater than startKey, less than or equal to endKey:
    item_value result = getTreapSum(parts2.right);
    //Merge the treaps back together:
    *treapPtr = mergeTreaps(mergeTreaps(parts2.left, parts2.right), parts.right);
    return result;
}

bool addElementByKey(struct treap **treapPtr, item_key newKey, item_value newValue, bool exclusive) {
    //Split treap up into a left-side with all elements less than newKey:
    struct treap_pair parts = splitByKey(*treapPtr, newKey, false);
    //Make sure newKey is not already in the tree:
    if (exclusive) {
        struct treap_pair parts2 = splitByKey(parts.left, newKey, true);
        if (parts2.right != NULL) {
            *treapPtr = mergeTreaps(mergeTreaps(parts2.left, parts2.right), parts.right);
            return false;
        }
        parts.left = mergeTreaps(parts2.left, parts2.right);
    }
    
    //Create a new node:
    struct treap *storeTreap = newTreap(newKey, newValue);
    //Put the new node to the right of the left-side, and then merge the new left-side with the right-side:
    *treapPtr = mergeTreaps(mergeTreaps(parts.left, storeTreap), parts.right);
    
    return true;
}

bool removeElementByKey(struct treap **treapPtr, item_key oldKey) {
    //Split treap up into a left-side which has all elements up to oldKey:
    struct treap_pair parts = splitByKey(*treapPtr, oldKey, false);
    //Now, split the left-side up into a left-side which has all elements before oldKey and a right-side which has all elements equal to oldKey:
    struct treap_pair parts2 = splitByKey(parts.left, oldKey, true);
    //Record whether there were actually any elements with oldKey:
    bool actuallyRemoved = parts2.right != NULL;
    //Merge treaps back together without the elements equal to oldKey:
    *treapPtr = mergeTreaps(parts2.left, parts.right);
    
    return actuallyRemoved;
}

typedef long long test_cases;
typedef long long weight;
typedef __int128 fraction;
typedef long long num_weights;
typedef long long num_ratios;

num_weights numMolecules;
weight molecules[400][2];
item_key curOrder;
fraction ratios[100000][2], curRatio[2];
num_ratios numRatios;
bool flag;

int compareRatios(const void *ptr1, const void *ptr2) {
    fraction *ratio1 = (fraction*)ptr1, *ratio2 = (fraction*)ptr2;
    //r1[0]/r1[1] < r2[0]/r2[1] -> r1[0]*r2[1]-r1[1]*r2[0] < 0
    fraction key = ratio1[0]*ratio2[1]-ratio1[1]*ratio2[0];
    if (key == 0) return 0;
    return (key > 0) ? 1 : -1;
}

int compareMolecules(const void *ptr1, const void *ptr2) {
    weight *mol1 = (weight*)ptr1, *mol2 = (weight*)ptr2;
    fraction key1 = mol1[0]*curRatio[0]+mol1[1]*curRatio[1];
    fraction key2 = mol2[0]*curRatio[0]+mol2[1]*curRatio[1];
    //printf("R %f | %lli %lli | %lli %lli | %f %f\n", curRatio, mol1[0], mol1[1], mol2[0], mol2[1], (double)key1, (double)key2);
    if (key1 == key2) {
        flag = true;
        return 0;
    }
    return (key1 > key2) ? 1 : -1;
}

int main() {
    num_weights i, j;
    num_ratios k;
    test_cases numTestCases, l;
    scanf("%lli", &numTestCases);
    
    REPEAT(l, numTestCases) {
        allOrders = NULL, numSpaceUsed = 0;
        scanf("%lli", &numMolecules);
        REPEAT(i, numMolecules) scanf("%lli %lli", molecules[i]+0, molecules[i]+1);
        
        numRatios = 0;
        REPEAT(i, numMolecules) {
            REPEAT(j, numMolecules) {
                ratios[numRatios][0] = molecules[j][1]-molecules[i][1];
                ratios[numRatios][1] = molecules[i][0]-molecules[j][0];
                if (ratios[numRatios][1] < 0) {
                    ratios[numRatios][0] *= -1;
                    ratios[numRatios][1] *= -1;
                }
                if ((ratios[numRatios][1] != 0) && (((double)(ratios[numRatios][0]))/((double)(ratios[numRatios][1])) > 0)) numRatios++;
            }
        }
        ratios[numRatios][0] = 1, ratios[numRatios][1] = 2000000000, numRatios++;
        ratios[numRatios][0] = 2000000000, ratios[numRatios][1] = 1, numRatios++;
        qsort(ratios, numRatios, 2*sizeof(fraction), compareRatios);
        
        REPEAT(k, numRatios) if (k > 0) {
            flag = false;
            //a/b+c/d=ad/(bd)+bc/(bd)=(ad+bc)/(bd)
            curRatio[0] = ratios[k-1][0]*ratios[k][1]+ratios[k-1][1]*ratios[k][0];
            curRatio[1] = ratios[k-1][1]*ratios[k][1]*2;
            
            memcpy(curOrder.arr, molecules, numMolecules*2*sizeof(weight));
            qsort(curOrder.arr, numMolecules, 2*sizeof(weight), compareMolecules);
            /*printf("%f %i\n", ((double)curRatio[0])/curRatio[1], (int)flag);
            printf("(");
            REPEAT(i, numMolecules) {
                printf("(%lli, %lli)", curOrder.arr[i][0], curOrder.arr[i][1]);
                if (i+1 == numMolecules) puts(")");
                else printf(", ");
            }*/
            if (!flag) addElementByKey(&allOrders, curOrder, 1, true);
        }
        printf("Case #%lli: %lli\n", l+1, getTreapSize(allOrders));
    }
    
    exit(0);
}