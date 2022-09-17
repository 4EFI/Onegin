#include <string.h>

#include "StringProcessing.h"
#include "FileAlgorithms.h"
#include "StrAlgorithms.h"
#include "OptionsCmdLine.h"
#include "LOG.h"

//-----------------------------------------------------------------------------

int CompDirectSorting  (const void * str1, const void * str2);
int CompReverseSorting (const void * str1, const void * str2);

//-----------------------------------------------------------------------------

//char HelpOptionNames[] = {"-h", "/h", "--help", "/?"};

//-----------------------------------------------------------------------------

int main (int argc, char *argv[])
{
    Text hamletText;

    if ( !hamletText.SetFile ("Hamlet.txt", "r") ) return -1;

    hamletText.SetLines();

    //TrimStrings (arrStrs, numLines);

    //Text hamletTextCopy = CopyLines (arrOrigStrs, arrStrs, numLines);

    FILE* fileOut = NULL;
    if ( !OpenFile (&fileOut, "fileOut.txt", "w") ) return -1;

    BubbleSort (hamletText.GetLines(), 
                hamletText.GetNumLines(), 
                sizeof (String), 
                &CompDirectSorting);

    PrintLines ( fileOut, hamletText.GetLines(), hamletText.GetNumLines() );

    /*
    BubbleSort (arrStrs, numLines, sizeof (String), &CompReverseSorting);
    PrintLines (fileOut, arrStrs, numLines);

    // Original
    PrintLines (fileOut, arrOrigStrs, numLines);

    //qsort (arrOrigStrs, numLines, sizeof (String), &CompDirectSorting);

    QuickSort (arrOrigStrs, numLines, sizeof (String), &CompDirectSorting);
    PrintLines (fileOut, arrOrigStrs, numLines);

    free (str);
    free (arrStrs);

    fclose (fileIn);
    fclose (fileOut);
    */

    return 0;
}

//-----------------------------------------------------------------------------

int CompDirectSorting (const void * str1, const void * str2)
{
    return strcmp ( ((const String*)str1)->str, ((const String*)str2)->str );
}

//-----------------------------------------------------------------------------

int CompReverseSorting (const void * str1, const void * str2)
{
    return StrReverseCmp ( ((const String*)str1)->str, ((const String*)str2)->str );
}

//-----------------------------------------------------------------------------
