#include "StrAlgorithm.h"
#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

const char IgnoredSymbols[] = " .!?:;-";

//-----------------------------------------------------------------------------

int DivideStr (char* str, StrParams* arrStrs[])
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (str != NULL);
    //}

    int numStrs = GetNumStrs (str);

    int strLen = strlen (str);

    *arrStrs = (StrParams*) calloc (sizeof (StrParams), numStrs);

    int pos = 0, nowStr = 0;

    for (int i = 0; i <= strLen; i++)
    {
        if (str[i] == '\n' || str[i] == '\0')
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

int GetNumStrs (char *str)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (str != NULL);
    //}

    int numStrs = 0;

    int strLen = strlen (str);

    for (int i = 0; i <= strLen; i++)
    {
        if (str[i] == '\n' || str[i] == '\0') numStrs++;
    }

    return numStrs;
}

//-----------------------------------------------------------------------------

int GetFileStr (FILE* file, char** str)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (file != NULL);
    assert (str  != NULL);
    //}

    int fileSize = GetFileSize (file);

    *str = (char*) calloc (sizeof (char), fileSize + 1);

    int rightRead = fread (*str, sizeof (char), fileSize, file);

    FillStr (*str, rightRead, fileSize - 1, '\0');

    return fileSize;
}

//-----------------------------------------------------------------------------

void FillStr (char* str, int iBeginStr, int iEndStr, char sym)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (str != NULL);
    //}

    int len = strlen (str);

    for (int i = iBeginStr; i <= iEndStr; i++)
    {
        str[i] = sym;
    }
}

//-----------------------------------------------------------------------------

int GetFileSize (FILE* file)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (file != NULL);
    //}

    fseek (file, 0, SEEK_END);

    int fileSize = ftell (file);

    FLOG ("fileSize = %d", fileSize);

    fseek (file, 0, SEEK_SET);

    return fileSize;
}

//-----------------------------------------------------------------------------

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd)
{
    //{ ASSERT
    assert ( str != NULL);
    assert (*str != NULL);
    //}

    bool isBegin = ( (iBegin < iEnd) ? true : false );

    int numIgnoredSyms = 0;

    int len = strlen (IgnoredSymbols);

    bool isWord = true;

    for (int i = (isBegin) ? iBegin    : iEnd;
                 (isBegin) ? i <= iEnd : i >= iBegin;
                 (isBegin) ? i++       : i--)
    {
        LOG ("i = %d", i);

        isWord = true;

        for (int curIgnoredSym = 0; curIgnoredSym < len; curIgnoredSym++)
        {
            if ((*str)[i] == IgnoredSymbols[curIgnoredSym])
            {
                numIgnoredSyms++;

                isWord = false;
                break;
            }
        }

        if (isWord)
        {
            if (isBegin)
            {
                *str = *str + iBegin + numIgnoredSyms;
            }
            else
            {
                *str = *str + iEnd   - numIgnoredSyms;

                LOG ("");
            }

            break;
        }
    }

    return numIgnoredSyms;
}

//-----------------------------------------------------------------------------

void BubbleSortStrings (StrParams* arrStrs[], int numStrs)
{
    int numIgnoredSyms = 0;

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

//-----------------------------------------------------------------------------

