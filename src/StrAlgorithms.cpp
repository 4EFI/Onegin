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

Text::~Text()
{
    if (allStr != NULL) free (allStr);
    if (lines  != NULL) free (lines);

    allStr = NULL;
    lines  = NULL;
}

//-----------------------------------------------------------------------------

long int Text::SetLines(FILE* file)
{
    //{ ASSERT
    assert (file != NULL);
    //}
    
    if (allStr == NULL) strSize = ReadAllFile (file, &allStr);    
    
    if (allStr != NULL) numLines = DivideStr (allStr, &lines);

    for (int i = 0; i < numLines; i++)
    {
        lines[i].numLeftIgnSyms  = NumLeftIgnoredSyms  ( lines[i].str );
        lines[i].numRightIgnSyms = NumRightIgnoredSyms ( lines[i].str );
    }

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

int NumLeftIgnoredSyms (const char* str, const char *ignoredSymbols)
{
    //{ ASSERT
    assert (str            != NULL);
    assert (ignoredSymbols != NULL);
    //}

    int numLeftIgnSyms = 0;

    for (int i = 0; ; i++)
    {
        // If end of str
        if (str[i] == '\0') break;

        if ( !strchr (ignoredSymbols, str[i]) ) break;

        numLeftIgnSyms++;
    }

    return numLeftIgnSyms;
}

//-----------------------------------------------------------------------------

int NumRightIgnoredSyms (const char* str, const char *ignoredSymbols)
{
    //{ ASSERT
    assert (str            != NULL);
    assert (ignoredSymbols != NULL);
    //}

    int lenStr = 0, lastStr = 0;

    for (int i = 0; ; i++)
    {
        // If end of str
        if (str[i] == '\0') break;

        if ( !strchr (ignoredSymbols, str[i]) ) lastStr = i;

        lenStr++;
    }

    return lenStr - (lastStr + 1);
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

    int numIgnoredSyms = NumLeftIgnoredSyms (*str, ignoredSymbols);

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

        if ( !strchr (ignoredSymbols, (*str)[i]) ) lastStr = i;

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
    
    //{ ASSERT
    assert (arr != NULL);
    //}

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

    //{ ASSERT
    assert (arr != NULL);
    //}
    
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
    //{ ASSERT
    assert (a != NULL);
    assert (b != NULL);
    //}
    
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

void CopyLines (String** strTo, const String* strFrom, int numLines)
{
    //{ ASSERT
    assert (strTo   != NULL);
    assert (strFrom != NULL);
    //}
    
    *strTo = (String*)calloc (numLines, sizeof (String)); 
    
    for (int i = 0; i < numLines; i++)
    {
        (*strTo)[i] = strFrom[i];
    }
}

//-----------------------------------------------------------------------------

void PrintLines (FILE* file, String* arrStrs, int numLines)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (file    != NULL);
    assert (arrStrs != NULL);
    //}
    
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

int StrReverseCmp (const char* str1, size_t len1, const char* str2, size_t len2)
{
    $LOG_LVL_UP
    
    //{ ASSERT
    assert (str1 != NULL);
    assert (str2 != NULL);
    //}

    if (len1 <= 0) len1 = strlen (str1);
    if (len2 <= 0) len2 = strlen (str2);
    
    size_t lenMin = std::min (len1, len2);

    for (size_t i = 1; i <= lenMin; i++)
    {        
        if      (str1[len1 - i] > str2[len2 - i]) return  1;
        else if (str1[len1 - i] < str2[len2 - i]) return -1;
    }

    if (len1 < len2) return -1;
    if (len1 > len2) return  1;

    return 0;
}

//-----------------------------------------------------------------------------