#include "StrAlgorithm.h"
#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

//-----------------------------------------------------------------------------

int GetFileStrs (FILE* file, StrParams* arrStrs[])
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (file != NULL);
    //}

    fseek (file, 0, SEEK_END);

    int fileSize = ftell (file);

    FLOG ("fileSize = %d", fileSize);

    char* str = (char*) calloc (sizeof (char), fileSize + 1);

    fseek (file, 0, SEEK_SET);

    int rightRead = fread (str, sizeof (char), fileSize, file);

    FLOG ("right read = %d",          rightRead);
    FLOG ("last str sym = '%c' = %d", str[fileSize], str[fileSize]);
    FLOG ("sizeof char ** = %d",      sizeof(char**));

    int numStrs = 0;

    for (int i = 0; i < fileSize; i++)
    {
        if (str[i] == '\n') numStrs++;
    }

    FLOG ("num strings = %d", numStrs);

    *arrStrs = (StrParams*) calloc (sizeof (StrParams), numStrs);

    int pos = 0, nowStr = 0;

    for (int i = 0; i < fileSize; i++)
    {
        if (str[i] == '\n')
        {
            (*arrStrs)[nowStr].str      = &str[i - pos];
            //+1 for '\0'
            (*arrStrs)[nowStr].len      = pos + 1;
            (*arrStrs)[nowStr].str[pos] = '\0';

            pos = 0;
            nowStr++;

            continue;
        }

        pos++;
    }

    return numStrs;
}

//-----------------------------------------------------------------------------

int RemoveLeadingSpaces (char** str, int strLen)
{
    int  numLeadingSpaces = 0;

    for (int i = 0; i < strLen; i++)
    {
        if ((*str)[i] == ' ')
        {
            numLeadingSpaces++;
        }
        else
        {
            *str += numLeadingSpaces;

            return numLeadingSpaces;
        }
    }
}

//-----------------------------------------------------------------------------

void BubbleSortStrings (StrParams* arrStrs[], int numStrs)
{
    for (int i = 0; i < numStrs; i++)
    {
        for (int j = 0; j < numStrs - i - 1; j++)
        {
            if ((*arrStrs)[j].str[0] > (*arrStrs)[j + 1].str[0])
            {
                std::swap ((*arrStrs)[j], (*arrStrs)[j + 1]);
            }
        }
    }
}
