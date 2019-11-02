#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

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
    int64_t x, y;
} item_key;
typedef int64_t item_value;
typedef int64_t num_items;

int compareKeys(item_key key1, item_key key2) {
    if (key1.x != key2.x) return key1.x-key2.x;
    return key1.y-key2.y;
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

struct treap space[60000];
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
    if (numSpaceUsed > 400000) fprintf(stderr, "Ran out of treap space"), exit(1);
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

void incrementValueOfKey(struct treap **treapPtr, item_key newKey) {
    //Split treap up into a left-side with all elements less than newKey:
    struct treap_pair parts = splitByKey(*treapPtr, newKey, false);
    //Make sure newKey is not already in the tree:
    struct treap_pair parts2 = splitByKey(parts.left, newKey, true);
    if (parts2.right != NULL) {
        parts2.right->value += 1;
        *treapPtr = mergeTreaps(mergeTreaps(parts2.left, parts2.right), parts.right);
        return;
    }
    parts.left = mergeTreaps(parts2.left, parts2.right);
    
    //Create a new node:
    struct treap *storeTreap = newTreap(newKey, 1);
    //Put the new node to the right of the left-side, and then merge the new left-side with the right-side:
    *treapPtr = mergeTreaps(mergeTreaps(parts.left, storeTreap), parts.right);
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

//Split treap into a left-side with the first pos elements and a right-side with the rest of the elements.
//The left-side will be rooted with the (pos-1)th item (0-based indexing), if it exists.
struct treap_pair splitByPos(struct treap *treap1, num_items pos) {
    struct treap_pair answer;
    if (treap1 == NULL) {
        answer.left = answer.right = NULL;
        return answer;
    }
    if (pos > treap1->size) {
        answer.left = treap1, answer.right = NULL;
        return answer;
    }
    
    num_items leftSize = getTreapSize(treap1->left);
    //If the left-side has pos elements or more, then the (pos-1)th element is on the left-side:
    if (pos <= leftSize) {
        answer = splitByPos(treap1->left, pos);
        //Since answer.left is the tree rooted at (pos-1)th element, make answer.right, the elements between the (pos-1)th element and the root, the new left node of the treap:
        treap1->left = answer.right;
        //After making this modification, treap1 becomes the right-side, which has all elements after the (pos-1)th one:
        answer.right = treap1;
    }
    //Otherwise, we need to split the right-side up to look for the (pos-1)th element:
    else {
        //Notice that we subtract pos by the number of elements in the root and left-side:
        answer = splitByPos(treap1->right, pos-leftSize-1);
        //Now, in order to get all of the first pos elements, we need to combine treap1 and its left-side with all of the elements in the right-side.
        //These elements are now in answer.left, so make answer.left the new right-side of treap:
        treap1->right = answer.left;
        //After making this modification, treap1 becomes the left-side, which has all of the first pos elements:
        answer.left = treap1;
    }
    calcTreapProperties(treap1);
    return answer;
}

typedef int64_t test_cases;
typedef int64_t coord;
typedef int64_t num_coords;
typedef int64_t num_people;

struct treap *root;
struct treap_pair storePair;
coord maxCoord, curX, curY, answerX, answerY;
num_people numPeople, maxPeople;
char direction[10];

int main() {
    test_cases numTestCases, l;
    num_people i;
    item_key storeKey;
    scanf("%" PRId64, &numTestCases);
    
    REPEAT(l, numTestCases) {
        root = NULL, numSpaceUsed = 0;
        
        scanf("%" PRId64 " %" PRId64, &numPeople, &maxCoord);
        REPEAT(i, numPeople) {
            scanf("%" PRId64 " %" PRId64 " %s", &curX, &curY, direction);
            switch (direction[0]) {
                case 'N':
                    REPEAT(storeKey.x, maxCoord+1) for (storeKey.y = curY+1; storeKey.y <= maxCoord; storeKey.y++) {
                        incrementValueOfKey(&root, storeKey);
                    }
                    break;
                case 'S':
                    REPEAT(storeKey.x, maxCoord+1) for (storeKey.y = curY-1; storeKey.y >= 0; storeKey.y--) {
                        incrementValueOfKey(&root, storeKey);
                    }
                    break;
                case 'E':
                    REPEAT(storeKey.y, maxCoord+1) for (storeKey.x = curX+1; storeKey.x <= maxCoord; storeKey.x++) {
                        incrementValueOfKey(&root, storeKey);
                    }
                    break;
                case 'W':
                    REPEAT(storeKey.y, maxCoord+1) for (storeKey.x = curX-1; storeKey.x >= 0; storeKey.x--) {
                        incrementValueOfKey(&root, storeKey);
                    }
                    break;
                default:
                    exit(1);
                    break;
            }
        }
        
        answerX = answerY = maxPeople = -1;
        while (getTreapSize(root) > 0) {
            storePair = splitByPos(root, 1);
            if (storePair.left->value > maxPeople) {
                answerX = storePair.left->key.x;
                answerY = storePair.left->key.y;
                maxPeople = storePair.left->value;
            }
            root = storePair.right;
        }
        printf("Case #%" PRId64 ": %" PRId64 " %" PRId64 "\n", l+1, answerX, answerY);
    }
    
    exit(0);
}