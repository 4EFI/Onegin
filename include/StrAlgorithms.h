#ifndef STR_ALGORITHM_H
#define STR_ALGORITHM_H

#include <stdio.h>

//-----------------------------------------------------------------------------

struct StrParams
{
    char* str = NULL;
    int   len = 0;
};

//-----------------------------------------------------------------------------

const char IgnoredSymbols[] = " .,()[]{}<>\\/|~`!?:;-'";

//-----------------------------------------------------------------------------

int DivideStr (char* str, StrParams** arrStrs);

int ReadAllFile (FILE* file, char **str);

int GetNumStrs (const char *str);

int GetFileSize (FILE* file);

int TrimLeftIgnoredSyms  (char** str, const char *ignoredSymbols = IgnoredSymbols);
int TrimRightIgnoredSyms (char** str, const char *ignoredSymbols = IgnoredSymbols);

void TrimStrings (StrParams arrStrs[], int numStrs, const char *ignoredSymbols = IgnoredSymbols);

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd);

void BubbleSort (void * arr, size_t numStrs, size_t size, int (*comparator)(const void * arr1, const void * arr2));

void Swap (void * a, void * b, size_t size);

//-----------------------------------------------------------------------------

#endif
