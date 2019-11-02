#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline char FASTIO(char *nextChar) { return (*nextChar = getchar()); }
static inline void FASTEX(void *ptr, char inputChar, size_t ptrSize) {
    ((ptrSize == sizeof(byte))
        ? (*((byte*)ptr) = (*((byte*)ptr))*10+(inputChar-'0'))
        : (ptrSize == sizeof(short))
            ? (*((short*)ptr) = (*((short*)ptr))*10+(inputChar-'0'))
            : (ptrSize == sizeof(int))
                ? (*((int*)ptr) = (*((int*)ptr))*10+(inputChar-'0'))
                : (ptrSize == sizeof(long))
                    ? (*((long*)ptr) = (*((long*)ptr))*10+(inputChar-'0'))
                    : (ptrSize == sizeof(long long))
                        ? (*((long long*)ptr) = (*((long long*)ptr))*10+(inputChar-'0'))
                        //This case will not be reached:
                        : 0);
}
static inline byte FASTEXS(void *ptr, char inputChar, size_t ptrSize) { return ((inputChar == '-') ? (-1) : (FASTEX(ptr, inputChar, ptrSize), 1)); }
static inline void FASTEXN(void *ptr, byte sign, char inputChar, size_t ptrSize) {
    ((ptrSize == sizeof(byte))
        ? (*((byte*)ptr) = (*((byte*)ptr))*10+sign*(inputChar-'0'))
        : (ptrSize == sizeof(short))
            ? (*((short*)ptr) = (*((short*)ptr))*10+sign*(inputChar-'0'))
            : (ptrSize == sizeof(int))
                ? (*((int*)ptr) = (*((int*)ptr))*10+sign*(inputChar-'0'))
                : (ptrSize == sizeof(long))
                    ? (*((long*)ptr) = (*((long*)ptr))*10+sign*(inputChar-'0'))
                    : (ptrSize == sizeof(long long))
                        ? (*((long long*)ptr) = (*((long long*)ptr))*10+sign*(inputChar-'0'))
                        //This case will not be reached:
                        : 0);
}
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

int main() {
    byte sign;
    char store;
    
    exit(0);
}