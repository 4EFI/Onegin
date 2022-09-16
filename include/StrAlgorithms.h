#ifndef STR_ALGORITHM_H
#define STR_ALGORITHM_H

#include <stdio.h>

//-----------------------------------------------------------------------------

struct StrParams
{
    char* str;
    int   len;
};

//-----------------------------------------------------------------------------

const char IgnoredSymbols[] = " .,()[]{}<>\\/|~`!?:;-'";

//-----------------------------------------------------------------------------

int DivideStr (char* str, StrParams** arrStrs);

long int ReadAllFile (FILE* file, char **str);

int GetNumStrs (const char *str);

long int GetFileSize (FILE* file);

int TrimLeftIgnoredSyms  (char** str, const char *ignoredSymbols = IgnoredSymbols);
int TrimRightIgnoredSyms (char** str, const char *ignoredSymbols = IgnoredSymbols);

void TrimStrings (StrParams arrStrs[], int numStrs, const char *ignoredSymbols = IgnoredSymbols);

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd);

void BubbleSort (void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2));
void QuickSort  (void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2));

void Swap (void * a, void * b, size_t size);

//-----------------------------------------------------------------------------

#endif
