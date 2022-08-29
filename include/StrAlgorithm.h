#ifndef STR_ALGORITHM_H
#define STR_ALGORITHM_H

#include <stdio.h>

//-----------------------------------------------------------------------------

// StrParams str = {0};
struct StrParams
{
    char* str = NULL; // C++??
    int   len = 0;
};

//-----------------------------------------------------------------------------

const char IgnoredSymbols[] = " .,()[]{}<>\\/|~`!?:;-";

//-----------------------------------------------------------------------------

int DivideStr (char* str, StrParams** arrStrs);

int ReadAllFile (FILE* file, char **str);

int GetNumStrs (const char *str);

int GetFileSize (FILE* file);

int TrimLeftIgnoredSyms  (char** str, const char *ignoredSymbols = IgnoredSymbols);
int TrimRightIgnoredSyms (char** str, const char *ignoredSymbols = IgnoredSymbols);

void TrimStrings (StrParams arrStrs[], int numStrs, const char *ignoredSymbols = IgnoredSymbols);

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd);

void BubbleSortStrings (StrParams arrStrs[], int numStrs);

//-----------------------------------------------------------------------------

#endif
