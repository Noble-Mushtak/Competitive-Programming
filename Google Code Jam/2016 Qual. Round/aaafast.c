#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef signed char byte;
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
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }
//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

int main() {
    char store;
    
    exit(0);
}