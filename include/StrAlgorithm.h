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

int GetFileStrs (FILE* file, StrParams* arrStrs[]);

//-----------------------------------------------------------------------------

int RemoveLeadingSpaces (char** str, int strLen);

//-----------------------------------------------------------------------------

void BubbleSortStrings (StrParams* arrStrs[], int numStrs);

//-----------------------------------------------------------------------------

#endif
