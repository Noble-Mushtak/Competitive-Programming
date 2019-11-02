/**
 * Fast I/O functions for C++
 * Documentation coming soon!
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <cinttypes>

//If we have the unlocked versions of these functions, then use them.
//According to https://linux.die.net/man/3/fread_unlocked,
//these functions are defined when _BSD_SOURCE or _SVID_SOURCE is defined.
//However, according to https://stackoverflow.com/questions/29201515/what-does-d-default-source-do,
//these macros are deprecated, so use _DEFAULT_SOURCE instead
#ifdef _DEFAULT_SOURCE
#define feof feof_unlocked
#define fread fread_unlocked
#define fwrite fwrite_unlocked
#endif

typedef int32_t num;

const size_t INPUT_SIZE = 32768;
const size_t OUTPUT_SIZE = 32768;
char inputBuffer[INPUT_SIZE], outputBuffer[OUTPUT_SIZE];
size_t numCharsInput, curInputPos, numCharsOutput;
bool reachedEOF = false;

static inline void readChars() {
    //Read characters from stdin
    numCharsInput = fread(inputBuffer, 1, INPUT_SIZE, stdin);
    //Update reachedEOF:
    reachedEOF = (feof(stdin) != 0);
    //Reset curInputPos:
    curInputPos = 0;
}

num readNum() {
    num result = 0, sign = 1;
    bool foundFirstDigit = false;
    char curChar;

    while (true) {
        //Read characters from stdin while needed:
        while (curInputPos >= numCharsInput) {
            //If we have reached EOF, then just return:
            if (reachedEOF) return sign*result;

            readChars();
        }
        curChar = inputBuffer[curInputPos++];

        //If the current character is a digit, then update result:
        if ((curChar >= '0') && (curChar <= '9')) {
            foundFirstDigit = true;
            result *= 10;
            result += (curChar-'0');
            continue;
        }
        //If we haven't found a digit yet, but we did find a hyphen, treat it like the start of a negative number:
        if ((curChar == '-') && !foundFirstDigit) {
            foundFirstDigit = true;
            sign = -1;
            continue;
        }
        //If the current character is not a digit and we have already found the first digit, then return:
        if (foundFirstDigit) return sign*result;
        //Otherwise, do nothing and continue looping until we find the first digit.
    }
}

static inline void flush() {
    size_t numCharsWritten = 0;
    //Keep writing characters until there are no more characters to write:
    while (numCharsWritten < numCharsOutput) numCharsWritten += fwrite(outputBuffer+numCharsWritten, 1, numCharsOutput-numCharsWritten, stdout);
    //Reset numCharsOutput:
    numCharsOutput = 0;
}

char numberBuffer[24];
void outputNum(num num1) {
    size_t numDigits = 0;
    bool isNegative = (num1 < 0);
    //Make num1 positive for now:
    if (isNegative) num1 *= -1;

    do {
        //Prepend a digit to the number:
        numberBuffer[23-numDigits] = (num1 % 10)+'0';
        //Get rid of the last digit by dividing by 10:
        num1 /= 10;
        numDigits++; //We just added a digit, so increment numDigits
    } while (num1 > 0);
    //Add hyphen to beginning if necessary:
    if (isNegative) {
        numberBuffer[23-numDigits] = '-';
        numDigits++;
    }

    //Copy numberBuffer to outputBuffer:
    memcpy(outputBuffer+numCharsOutput, numberBuffer+(24-numDigits), numDigits*sizeof(char));
    //Update numCharsOutput:
    numCharsOutput += numDigits;
    //Flush if another number would not fit in this buffer:
    if (numCharsOutput+24 > OUTPUT_SIZE) flush();
}

int main() {
    num numNums = readNum();
    while (numNums--) {
        num curNum = readNum();
        outputNum(curNum);
        outputBuffer[numCharsOutput++] = '\n';
    }
    flush();
    puts("END");
    
    exit(0);
}