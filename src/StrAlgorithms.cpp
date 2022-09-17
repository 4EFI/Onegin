//#define NLOG

#include "StrAlgorithms.h"
#include "FileAlgorithms.h"
#include "LOG.h"

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

// Text
//-----------------------------------------------------------------------------

bool Text::SetFile (const char * fileName, const char * typeOpen)
{
    return OpenFile (&file, fileName, typeOpen);
}

//-----------------------------------------------------------------------------

long int Text::SetStr()
{
    strSize = ReadAllFile (file, &allStr);
    
    return strSize;
}

//-----------------------------------------------------------------------------

long int Text::SetLines()
{
    if (allStr == NULL) SetStr();    
    
    if (allStr != NULL) numLines = DivideStr (allStr, &lines);

    return numLines;
}

//-----------------------------------------------------------------------------
// End Text 

int DivideStr (char* str, String** arrStrs)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (str != NULL);
    //}

    int numStrs = GetNumStrs (str);

    *arrStrs = (String*) calloc (sizeof (String), numStrs);

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

void TrimStrings (String arrStrs[], int numStrs, const char* ignoredSymbols)
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

void BubbleSort ( void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2) )
{
    $LOG_LVL_UP
    
    for (size_t i = 0; i < num; i++)
    {
        for (size_t j = 0; j < num - i - 1; j++)
        {
            if ( comparator ( (char*)arr + j * size, (char*)arr + (j + 1) * size) > 0 )
            {            
                Swap ( (char*)arr + j * size, (char*)arr + (j + 1) * size, size );
            }
        }
    }
}

//-----------------------------------------------------------------------------

void QuickSort ( void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2) )
{
    $LOG_LVL_UP
    
    size_t beginArr = 0;
    size_t endArr   = num - 1;

    void * middle = (char*)arr + (num / 2) * size;

    while (beginArr <= endArr)
    {    
        while ( comparator ( (char*)arr + beginArr * size, middle) < 0 ) 
        {
            beginArr++;
        }

        while ( comparator ( (char*)arr + endArr   * size, middle) > 0 ) 
        {
            endArr--;
        }

        if (beginArr <= endArr) 
        {
            // Swap (arr[beginArr], arr[endArr])
            Swap ( (char*)arr + beginArr * size, (char*)arr + endArr * size, size );

            beginArr++;
            endArr--;
        }
    } 

    if (endArr   > 0      ) QuickSort ( (char*)arr,                   endArr + 1,        size, comparator );
    if (beginArr < num - 1) QuickSort ( (char*)arr + beginArr * size, num    - beginArr, size, comparator );
}

//-----------------------------------------------------------------------------

void Swap (void * a, void * b, size_t size)
{
    char * str1 = (char*)a;
    char * str2 = (char*)b;
    char   temp = '\0';

    for (size_t i = 0; i < size; i++)
    {
        temp = str1[i];

        str1[i] = str2[i];
        str2[i] = temp;
    }
}

//-----------------------------------------------------------------------------

void CopyLines (String strTo[], const String strFrom[], int numLines)
{
    for (int i = 0; i < numLines; i++)
    {
        strTo[i] = strFrom[i];
    }
}

//-----------------------------------------------------------------------------

void PrintLines (FILE* file, String* arrStrs, int numLines)
{
    $LOG_LVL_UP
    
    int pos = 0;
    
    for (int i = 0; i < numLines; i++)
    {
        if ( arrStrs[i].str[0] == '\0' )
        {
            continue;
        }

        pos++;
        
        fprintf (file, "%4d) \"%s\"\n", pos, arrStrs[i].str);
    }
}

//-----------------------------------------------------------------------------
