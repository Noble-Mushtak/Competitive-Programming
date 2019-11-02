/**
 * struct String (and functions) for C
 * 
 * Properties:
 * char *str: Array of characters (not necessary a null-terminated C string)
 * long length: Length of string
 * long size: Allocated Size of string (0 if not allocated)
 * bool allocated: 1 iff .str was allocated and should be freed.
 *
 * Constants:
 * String DEFAULT_STR
 * * The default String. Set Strings to DEFAULT in the initializer. For example:
 * * * String hi = DEFAULT_STR;
 * * * [...]
 * 
 * Functions:
 * void allocate_str(String *str, long length, bool free_str)
 * * Set str such that it has .str = empty array of characters with length (the length argument) and .size = least power of 2 greater than length. .size = 32 if length < 32. str->str if freed if str->allocated and free_str are true.
 * 
 * String make_str(const char *string)
 * * Returns allocated String with the initial characters of .str being equal to the characters of (the string argument) before the null.
 * 
 * String convert_string_to_str(char *string)
 * * Returns String with .str = string, .length = number of characters in string before the null, and .size = .length. String returned is not allocated from allocate_str().
 * 
 * char* convert_str_to_string(String str)
 * * Returns null-terminated C string from str.str and str.length. Allocated from malloc().
 * 
 * String add_strs(String str1, String str2)
 * * Return String with .str = concatenation of str1.str and str2.str. String returned is allocated from allocate_str().
 * 
 * void add_str_to_str(String *str, String appendee)
 * * Concatenates appendee.str onto str->str. Allocates str from allocate_str() if str->size implies that str->str is not big enough for appendee to be appended.
 * 
 * inline void add_string_to_str(String *str, char *string)
 * * Equivalent to add_str_to_str(str, convert_string_to_str(string));
 * 
 * String substr(const String *str, long beg_ind, long end_ind, long skip)
 * * Returns String with .str = a pointer to another element in str->str based on beg_ind and .length based on beg_ind and end_ind. Similar to String.prototype.substring() in JavaScript and returns DEFAULT_STR for empty string or invalid interval.
 * 
 * String str_slice(const String *str, long beg_ind, long end_ind)
 * * Returns String sliced from str. Similar to Python string slicing and returns DEFAULT_STR for empty string. If not DEFAULT_STR, String returned is allocated with allocate_str().
 *
 * long str_index(const String *str, String substr)
 * * Returns index of first instance of substr.str in str.str from left (-1 if substr does not occur).
 * 
 * inline long str_string_index(const String *str, const char *substring)
 * * Equivalent to str_index(str, convert_string_to_str(substring))
 *
 * long str_rindex(const String *str, String substr)
 * * Returns index of first instance of substr.str in str.str from right (-1 if substr does not occur).
 * 
 * inline long str_string_rindex(const String *str, const char *substring)
 * * Equivalent to str_rindex(str, convert_string_to_str(substring))
 * 
 * int printf_str(String str)
 * * Prints str onto standard output using putchar(). Returns number of characters successfully outputted.
 * 
 * int fprintf_str(FILE *file, String str)
 * * Prints str onto file using fputc(). Returns number of characters successfully outputted.
 * 
 * int str_scanf(String str, const char *format, ...)
 * * Works similar to sscanf(convert_str_to_string(str), format, ...), except uses vsscanf and frees converted C string from str.
 * 
 * int str_vscanf(String str, const char *format, ...)
 * * Works similar to vsscanf(convert_str_to_string(str), format, ...), except frees converted C string from str.
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

typedef struct {
    char *str;
    long length;
    long size;
    bool allocated;
} String;
const String DEFAULT_STR = { .str = NULL, .length = 0, .size = 0, .allocated = false };

void allocate_str(String *str, long length, bool free_str) {
    //Set length accordingly
    str->length = length;
    //Set size to the maximum of the least power of 2 above length and 32.
    if (length < 32) str->size = 32;
    else str->size = (long) pow(2, logb(length)+1);
    //If free_str and the the old space inside str was dynamically allocated, free the space.
    if (free_str && str->allocated) free(str->str);
    //Allocate the space needed for str->str and set allocated to true.
    str->str = (char*) malloc(str->size*sizeof(char));
    str->allocated = true;
}

String make_str(const char *string) {
    String str = DEFAULT_STR;
    //Find the length of the string and allocate str accordingly.
    long i = 0;
    while (string[i] != '\0') i++;
    allocate_str(&str, i, true);
    //Copy from string to str.str and return str.
    memcpy(str.str, string, i*sizeof(char));
    return str;
}

String convert_string_to_str(char *string) {
    String str = DEFAULT_STR;
    //Find the length of the string.
    while (string[str.length] != '\0') str.length++;
    //Set str.str to string.
    str.str = string;
    //Set str.size to length and return str.
    str.size = str.length+1;
    return str;
}

char* convert_str_to_string(String str) {
    //Allocate our new C-string.
    char *string = (char*) malloc((str.length+1)*sizeof(char));
    //Copy from str.str over to string.
    memcpy(string, str.str, str.length*sizeof(char));
    //Add a NULL at the end of string and return string.
    string[str.length] = '\0';
    return string;
}

String add_strs(String str1, String str2) {
    //Our new string.
    String newStr = DEFAULT_STR;
    //Allocate our new string accordingly.
    allocate_str(&newStr, str1.length+str2.length, true);
    //Copy the first string into newStr.str.
    memcpy(newStr.str, str1.str, str1.length*sizeof(char));
    //Copy the second string into newStr.str after the first string.
    memcpy(newStr.str+str1.length, str2.str, str2.length*sizeof(char));
    //Return newStr.
    return newStr;
}

void add_str_to_str(String *str, String appendee) {
    //Properties of str to be accessed after str is reset with allocate_str().
    long oldLength = str->length;
    char *store = str->str;
    bool wasAllocated = str->allocated;
    
    if (str->size <= str->length+appendee.length) {
        //Allocate str for more space.
        allocate_str(str, oldLength+appendee.length, false);
        //Copy from store to str->str.
        memcpy(str->str, store, oldLength*sizeof(store));
        //Free store if it was dynamically allocated.
        if (wasAllocated) free(store);
    }
    //Otherwise, just set length.
    else str->length += appendee.length;
    
    //Copy the new string into str->str after the old string.
    memcpy(str->str+oldLength, appendee.str, appendee.length*sizeof(char));
}

inline void add_string_to_str(String *str, char *string) {
    //Simply convert the C-string to a String and call add_str_to_str().
    add_str_to_str(str, convert_string_to_str(string));
}

String substr(const String *str, long beg_ind, long end_ind) {
    //Our new string
    String sliced = DEFAULT_STR;
    //If end_ind is too big, set end_ind to str->length.
    if (end_ind > str->length) end_ind = str->length;
    //If the interval beg_ind is too big or too small, or end_ind is too small, return DEFAULT_STR.
    if (beg_ind >= end_ind || beg_ind < 0 || end_ind < 0) return sliced;
    //Set sliced.str, sliced.length, sliced.size, and sliced.allocated accordingly and return sliced.
    sliced.str = str->str+beg_ind;
    sliced.length = end_ind-beg_ind;
    sliced.size = str->size-beg_ind;
    //Set allocated to false because this pointer was not dynamically allocated even if str->str was.
    sliced.allocated = false;
    return sliced;
}

String str_slice(const String *str, long beg_ind, long end_ind, long skip) {
    //Set sliced to the default string.
    String sliced = DEFAULT_STR;
    //A variable for a for loop
    long i;
    
    //If beg_ind is less than -str->length, make it 0.
    if (beg_ind < -str->length) beg_ind = 0;
    //Otherwise, if beg_ind is negative, add to it by str->length.
    else if (beg_ind < 0) beg_ind += str->length;
    //Otherwise, if beg_ind is greater than or equal to str->length, return DEFAULT_STR.
    else if (beg_ind >= str->length) return sliced;

    //If end_ind is less than -str->length, make it 0.
    if (end_ind < -str->length) return sliced;
    //Otherwise, if end_ind is less than 0, add to it by str->length.
    else if (end_ind < 0) end_ind += str->length;
    //Otherwise, if str_ind is greater than str->length, make it str->length.
    else if (end_ind > str->length) end_ind = str->length;

    //If beg_ind is greater than end_ind, return an empty string:
    if (beg_ind > end_ind) return sliced;

    //Allocate sliced, set sliced.str accordingly, and return sliced.
    allocate_str(&sliced, (end_ind-beg_ind)/skip+(((end_ind-beg_ind) % skip) ? 1 : 0), true);
    for (i = beg_ind; i < end_ind; i+=skip) sliced.str[(i-beg_ind)/skip] = str->str[i];
    return sliced;
}

long str_index(const String *str, String substr) {
    //Variables used in for loops
    long i, j;
    //True iff looking for the substring worked.
    bool worked;
    //Loop through str->str and repeatedly check if the substring is at index i.
    for (i = 0; i <= str->length-substr.length; i++) {
        //Set worked to true.
        worked = true;
        //Set worked to false and exit this loop if we find a character that doesn't match.
        for (j = 0; j < substr.length; j++) if (str->str[i+j] != substr.str[j]) {
            worked = false;
            break;
        }
        //If the substring has been found, return the index.
        if (worked) return i;
    }
    //Return -1 if the substring is never found.
    return -1;
}

inline long str_string_index(const String *str, const char *substring) {
    //Convert the C-string to a String and call str_index().
    return str_index(str, convert_string_to_str((char*)substring));
}

long str_rindex(const String *str, String substr) {
    //This is exactly the same as str_index(), except we loop through str->str backwards instead of forwards.
    long i, j;
    bool worked;
    for (i = str->length-substr.length; i >= 0; i--) {
        worked = true;
        for (j = 0; j < substr.length; j++) if (str->str[i+j] != substr.str[j]) {
            worked = false;
            break;
        }
        if (worked) return i;
    }
    return -1;
}

inline long str_string_rindex(const String *str, const char *substring) {
    //Convert the C-string to a String and call str_rindex().
    return str_rindex(str, convert_string_to_str((char*)substring));
}

int printf_str(String str) {
    //A variable used for a for loop.
    long i;
    //A storage int, the number of characters successfully outputted.
    int store, returned = 0;
    //Loop through str.str and output each character. Increment returned if successful.
    for (i = 0; i < str.length; i++) {
        store = putchar(str.str[i]);
        if (store != EOF) returned++;
    }
    //Return returned.
    return returned;
}

int fprintf_str(FILE *file, String str) {
    //This is exactly the same as printf_str(), except we call fputc(str.str[i], file) instead of putchar(str.str[i]).
    long i;
    int store, returned = 0;
    for (i = 0; i < str.length; i++) {
        store = fputc(str.str[i], file);
        if (store != EOF) returned++;
    }
    return returned;
}

int str_scanf(String str, const char *format, ...) {
    //The value returned by vsscanf().
    int returned;
    //The argument list.
    va_list all_args;
    //Convert the String to a C-string.
    char *input_string = convert_str_to_string(str);
    //Start the argument list.
    va_start(all_args, format);
    //Call vsscanf() with input_string and all_args and set returned accordingly.
    returned = vsscanf(input_string, format, all_args);
    //End the argument list, free input_string, and return returned.
    va_end(all_args);
    free(input_string);
    return returned;
}

int str_vsscanf(String str, const char *format, va_list pointers) {
    //The value returned by vsscanf().
    int returned;
    //Convert the String to a C-string.
    char *input_string = convert_str_to_string(str);
    //Call vsscanf() with input_string and pointers and set returned accordingly.
    returned = vsscanf(input_string, format, pointers);
    //Free input_string and return returned.
    free(input_string);
    return returned;
}