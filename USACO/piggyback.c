/*
   PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=491
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#define DEBUGTIME
#ifdef DEBUGTIME
#include <time.h>
#define INITTIME() long long start = time(0)
#define PRINTTIME() printf("%lli\n", time(0)-start)
#else
#define INITTIME() 1
#define PRINTTIME() 1
#endif
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define SENTINEL 40000

typedef long field;
typedef long num_fields;
typedef long energy;
typedef long num_connections;
#define MAXLENGTH 50
typedef struct connection {
    num_fields length;
    field list[MAXLENGTH];
    struct connection *next;
} connection;
void insert(connection *list, field item) {
    while (list->length == MAXLENGTH) {
        if (list->next == NULL) {
            list->next = malloc(sizeof(connection));
            list->next->length = 0;
            list->next->next = NULL;
        }
        list = list->next;
    }
    list->list[list->length] = item;
    list->length++;
}

FILE *in, *out;
field stack[40000];
num_fields dists[40000], bessDists[40000], elDists[40000], barn, stackPos;
energy elEnergy, bessEnergy, groupEnergy, answer;
num_connections connectionsLength;
connection connections[40000];
bool added[40000];
long count = 0;

void runAlgo(num_fields *distances, field source) {
    field j, store;
    num_fields i, storeLength;
    connection *cur;
    
    REPEAT(i, 40000) added[i] = distances[i] = false;
    stack[0] = source;
    stackPos = 1;
    added[source] = true;
    while (stackPos) {
        stackPos--;
        store = stack[0];
        memmove(stack, stack+1, stackPos*sizeof(field));
        cur = connections+store;
        while (cur != NULL) {
            storeLength = cur->length;
            REPEAT(i, storeLength) if (!added[cur->list[i]]) {
                j = cur->list[i];
                distances[j] = distances[store]+1;
                stack[stackPos] = j;
                stackPos++;
                added[j] = true;
            }
            cur = cur->next;
        }
    }
}

int main() {
    field store, store2, i, i2, j;
    num_fields count;
    num_connections l;
    energy storeAnswer;
    INITTIME();
    
    in = fopen("piggyback.in", "r");
    fscanf(in, "%li %li %li %li %li", &bessEnergy, &elEnergy, &groupEnergy, &barn, &connectionsLength);
    REPEAT(l, connectionsLength) {
        fscanf(in, "%li %li", &store, &store2);
        insert(connections+(store-1), store2-1);
        insert(connections+(store2-1), store-1);
    }
    fclose(in);
    
    runAlgo(dists, barn-1);
    runAlgo(bessDists, 0);
    runAlgo(elDists, 1);
    answer = bessEnergy*dists[0]+elEnergy*dists[1];
    if (bessEnergy+elEnergy > groupEnergy) REPEAT(i, barn-1) {
        storeAnswer = bessEnergy*bessDists[i]+elEnergy*elDists[i]+groupEnergy*dists[i];
        if (storeAnswer < answer && (i == 0 || bessDists[i]) && (i == 1 || elDists[i]) && dists[i]) answer = storeAnswer;
    }
    
    out = fopen("piggyback.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    PRINTTIME();
    exit(0);
}