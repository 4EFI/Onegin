#include <string.h>

#include "../include/StringProcessing.h"
#include "../include/StrAlgorithms.h"
#include "../LOG/LOG.h"

//-----------------------------------------------------------------------------

bool OpenFile (FILE** file, const char* fileName, 
                            const char* typeOpen, 
                            const char* errorOpenning = "An error during opening file...\n");

void PrintLines (FILE* file, StrParams* arrStrs, int numLines);

void CopyLines (StrParams strTo[], const StrParams strFrom[], int numLines);

int CompDirectSorting  (const void * str1, const void * str2);
int CompReverseSorting (const void * str1, const void * str2);

//-----------------------------------------------------------------------------

int main()
{   
    FILE* fileIn = NULL;

    if ( !OpenFile (&fileIn, "Hamlet.txt", "r") ) return -1;

    char* str = NULL;

    ReadAllFile (fileIn, &str);

    StrParams* arrStrs = NULL;
    int numLines = DivideStr (str, &arrStrs);

    TrimStrings (arrStrs, numLines);

    StrParams arrOrigStrs[numLines] = {};

    CopyLines (arrOrigStrs, arrStrs, numLines);

    FILE* fileOut = NULL;

    if ( !OpenFile (&fileOut, "fileOut.txt", "w") ) return -1;

    BubbleSort (arrStrs, numLines, sizeof (StrParams), &CompDirectSorting);

    PrintLines (fileOut, arrStrs, numLines);

    BubbleSort (arrStrs, numLines, sizeof (StrParams), &CompReverseSorting);

    PrintLines (fileOut, arrStrs, numLines);

    PrintLines (fileOut, arrOrigStrs, numLines);

    qsort (arrOrigStrs, numLines, sizeof (StrParams), &CompDirectSorting);

    PrintLines (fileOut, arrOrigStrs, numLines);

    fclose (fileIn);
    fclose (fileOut);

    return 0;
}

//-----------------------------------------------------------------------------

bool OpenFile (FILE** file, const char* fileName, 
                            const char* typeOpen, 
                            const char* errorOpenning)
{
    *file = fopen (fileName, typeOpen);

    if ( !(*file) )
    {
        printf ("%s", errorOpenning);
        
        return 0; 
    }

    return 1;
}   

//-----------------------------------------------------------------------------

void PrintLines (FILE* file, StrParams* arrStrs, int numLines)
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

void CopyLines (StrParams strTo[], const StrParams strFrom[], int numLines)
{
    for (int i = 0; i < numLines; i++)
    {
        strTo[i] = strFrom[i];
    }
}

//-----------------------------------------------------------------------------

int CompDirectSorting (const void * str1, const void * str2)
{
    return strcmp ( ((StrParams*)str1)->str, ((StrParams*)str2)->str );
}

//-----------------------------------------------------------------------------

int CompReverseSorting (const void * str1, const void * str2)
{
    return StrReverseCmp ( ((StrParams*)str1)->str, ((StrParams*)str2)->str );
}

//-----------------------------------------------------------------------------
