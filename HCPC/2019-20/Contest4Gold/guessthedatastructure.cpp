#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <stack>
#include <queue>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_commands;
typedef int64_t command;
typedef int64_t element;

num_commands numCommands;
       
int main() {
    while (true) {
        scanf("%" PRId64, &numCommands);
        if (feof(stdin)) break;
        std::stack<element> curStack;
        std::queue<element> curQueue;
        std::priority_queue<element> curHeap;
        bool stackValid = true;
        bool queueValid = true;
        bool heapValid = true;
        
        num_commands i;
        REP(i, numCommands) {
            command com;
            element elem;
            scanf("%" PRId64 " %" PRId64, &com, &elem);
            if (com == 1) {
                curStack.push(elem);
                curQueue.push(elem);
                curHeap.push(elem);
            } else {
                stackValid &= !curStack.empty() && (elem == curStack.top());
                queueValid &= !curQueue.empty() && (elem == curQueue.front());
                heapValid &= !curHeap.empty() && (elem == curHeap.top());
                if (!curStack.empty()) curStack.pop();
                if (!curQueue.empty()) curQueue.pop();
                if (!curHeap.empty()) curHeap.pop();
            }
        }
        if (!stackValid && !queueValid && !heapValid) puts("impossible");
        else if (stackValid && !queueValid && !heapValid) puts("stack");
        else if (!stackValid && queueValid && !heapValid) puts("queue");
        else if (!stackValid && !queueValid && heapValid) puts("priority queue");
        else puts("not sure");
    }
    return 0;
}