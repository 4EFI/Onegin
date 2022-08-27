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

int DivideStr (char* str, StrParams* arrStrs[]);

int GetFileStr (FILE* file, char **str);

int GetNumStrs (char *str);

void FillStr (char* str, int iBeginStr, int iEndStr, char sym);

int GetFileSize (FILE* file);

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd);

void BubbleSortStrings (StrParams* arrStrs[], int numStrs);

//-----------------------------------------------------------------------------

#endif
