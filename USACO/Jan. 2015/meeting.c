#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef byte num_fields;
typedef byte field;
typedef short num_paths;
typedef long distance;
typedef long long num_alls;

FILE *in, *out;
num_paths numPaths;
num_fields length;
distance bessDistances[100][100], elsieDistances[100][100];

typedef long long item_length;
typedef distance item_type;
typedef struct vector {
    item_length size;
    item_length length;
    item_type *list;
} vector;

void insertItem(vector *list, item_type item) {
    item_type *store;
    while (list->length == list->size) {
        store = list->list;
        list->size *= 2;
        list->list = malloc(list->size*sizeof(item_type));
        memcpy(list->list, store, list->length*sizeof(item_type));
    }
    list->list[list->length] = item;
    list->length++;
}

item_type list[10000], list2[10000];
vector bess = { .length = 0, .size = 10000, .list = list }, elsie = { .length = 0, .size = 10000, .list = list2 };

short calcPaths(field at, distance bessDist, distance elsieDist) {
    field i;
    if (at+1 == length) insertItem(&bess, bessDist), insertItem(&elsie, elsieDist);
    else for (i = at+1; i < length; i++) if (bessDistances[at][i] < 101) calcPaths(i, bessDist+bessDistances[at][i], elsieDist+elsieDistances[at][i]);
}

int main() {
    distance min = LONG_MAX, *bessPosses, *elsiePosses;
    num_fields i, j;
    num_paths l, _d[4];
    field from, _h[4], to;
    num_alls m, n;
    
    in = fopen("meeting.in", "r");
    fscanf(in, "%hhi %hi", &length, &numPaths);
    REPEAT(i, length) for (j = i+1; j < length; j++) bessDistances[i][j] = elsieDistances[i][j] = 101;
    REPEAT(l, numPaths) {
        fscanf(in, "%hhi %hhi", &from, &to);
        from--, to--;
        fscanf(in, "%li %li", bessDistances[from]+to, elsieDistances[from]+to);
    }
    fclose(in);
    
    calcPaths(0, 0, 0);
    REPEAT(m, bess.length) REPEAT(n, elsie.length) if (bess.list[m] == elsie.list[n] && min > bess.list[m]) min = bess.list[m];
    
    out = fopen("meeting.out", "w");
    if (min == LONG_MAX) fprintf(out, "IMPOSSIBLE\n");
    else fprintf(out, "%li\n", min);
    fclose(out);
    
    exit(0);
}