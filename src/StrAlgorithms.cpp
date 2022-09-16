//#define NLOG

#include "../include/StrAlgorithms.h"
#include "../LOG/LOG.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

//-----------------------------------------------------------------------------

int DivideStr (char* str, StrParams** arrStrs)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (str != NULL);
    //}

    int numStrs = GetNumStrs (str);

    *arrStrs = (StrParams*) calloc (sizeof (StrParams), numStrs);

    int pos = 0, nowStr = 0;

    for (int i = 0; ; i++)
    {
        if (str[i] == '\n' || str[i] == '\0')
        {
            (*arrStrs)[nowStr].str = &str[i - pos];
            // +1 for '\0'
            (*arrStrs)[nowStr].len = pos + 1;

            // If end of str
            if (str[i] == '\0') break;

            (*arrStrs)[nowStr].str[pos] = '\0';
            // If \r
            if (pos > 0 && (*arrStrs)[nowStr].str[pos - 1] == '\r')
            {
                (*arrStrs)[nowStr].str[pos - 1] = '\0';
            }

            pos = 0;
            nowStr++;

            continue;
        }

        pos++;
    }

    return numStrs;
}

//-----------------------------------------------------------------------------

int GetNumStrs (const char *str)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (str != NULL);
    //}

    int numStrs = 0;

    for (int i = 0; ; i++)
    {
        if (str[i] == '\n' || str[i] == '\0')
        {
            numStrs++;

            if (str[i] == '\0') break;
        }
    }

    return numStrs;
}

//-----------------------------------------------------------------------------

int ReadAllFile (FILE* file, char** str)
{
    $LOG_LVL_UP

    // ASSERT
    assert (file != NULL);
    assert (str  != NULL);
    //

    int fileSize = GetFileSize (file);

    *str = (char*) calloc (sizeof (char), fileSize + 1);

    int rightRead = fread (*str, sizeof (char), fileSize, file);

    if (rightRead < fileSize)
        realloc ( str, sizeof (char) * (rightRead + 1) ); // Windows specific, \r remove

    (*str)[rightRead] = '\0';

    return rightRead;
}

//-----------------------------------------------------------------------------

int GetFileSize (FILE* file) //fstat
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (file != NULL);
    //}

    int curPos = ftell (file);

    fseek (file, 0, SEEK_END);

    int fileSize = ftell (file);

    fseek (file, curPos, SEEK_SET);

    FLOG ("fileSize = %d", fileSize);

    return fileSize;
}

//-----------------------------------------------------------------------------

// str_ptr
int TrimLeftIgnoredSyms (char** str, const char *ignoredSymbols)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert ( str           != NULL);
    assert (*str           != NULL);
    assert (ignoredSymbols != NULL);
    //}

    int numIgnoredSyms = 0;

    // char* str = *str_ptr;

    for (int i = 0; ; i++)
    {
        // If end of str
        if ((*str)[i] == '\0') break;

        if ( !strchr (ignoredSymbols, (*str)[i]) ) break;

        numIgnoredSyms++;
    }

   *str += numIgnoredSyms;

    return numIgnoredSyms;
}

//-----------------------------------------------------------------------------

// char**??
int TrimRightIgnoredSyms (char **str, const char *ignoredSymbols)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert ( str           != NULL);
    assert (*str           != NULL);
    assert (ignoredSymbols != NULL);
    //}

    int lenStr = 0, lastStr = 0;

    for (int i = 0; ; i++)
    {
        // If end of str
        if ((*str)[i] == '\0') break;

        if ( !strchr (ignoredSymbols, (*str)[i]) )
        {
            lastStr = i;
        }

        lenStr++;
    }

    int numIgnoredSyms = lenStr - (lastStr + 1);

    (*str)[lenStr - numIgnoredSyms] = '\0';

    return numIgnoredSyms;
}

//-----------------------------------------------------------------------------

void TrimStrings (StrParams arrStrs[], int numStrs, const char* ignoredSymbols)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (arrStrs        != NULL);
    assert (ignoredSymbols != NULL);
    //}

    for (int i = 0; i < numStrs; i++)
    {
        TrimLeftIgnoredSyms  (&arrStrs[i].str, ignoredSymbols);
        TrimRightIgnoredSyms (&arrStrs[i].str, ignoredSymbols);
    }
}

//-----------------------------------------------------------------------------

void BubbleSort (void * arr, size_t numStrs, size_t size, int (*comparator)(const void * arr1, const void * arr2))
{
    $LOG_LVL_UP
    
    LOG ("Arr = %lld; %lld", arr, (char*)arr);
    
    for (size_t i = 0; i < numStrs; i++)
    {
        for (size_t j = 0; j < numStrs - i - 1; j++)
        {
            if ( comparator (arr + j * size, arr + (j + 1) * size) > 0 )
            {            
                Swap (arr + j * size, arr + (j + 1) * size, size);
            }
        }
    }
}

//-----------------------------------------------------------------------------

void Swap (void * a, void * b, size_t size)
{
    char * str1 = (char*)a;
    char * str2 = (char*)b;
    char temp = '\0';

    for (size_t i = 0; i < size; i++)
    {
        temp = str1[i];

        str1[i] = str2[i];
        str2[i] = temp;
    }
}

//-----------------------------------------------------------------------------