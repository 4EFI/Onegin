#include <string.h>

#include "StringProcessing.h"
#include "FileAlgorithms.h"
#include "StrAlgorithms.h"
#include "OptionsCmdLine.h"
#include "LOG.h"

//-----------------------------------------------------------------------------

int CompDirectSorting  (const void * ptr_str1, const void * ptr_str2);
int CompReverseSorting (const void * ptr_str1, const void * ptr_str2);

//-----------------------------------------------------------------------------

//char HelpOptionNames[] = {"-h", "/h", "--help", "/?"};

//-----------------------------------------------------------------------------

int main (int argc, char *argv[])
{
    FILE* fileIn = NULL;
    if ( !OpenFile (&fileIn, "Hamlet.txt", "r") ) return -1;
    
    Text hamletText = {0};
    TextInit (&hamletText);

    TextSetFileLines (&hamletText, fileIn);

    Text hamletTextCopy = hamletText;
    CopyLines (&hamletTextCopy.lines, hamletText.lines, hamletText.numLines);
    hamletText.isCopyStr = true;

    FILE* fileOut = NULL;
    if ( !OpenFile (&fileOut, "fileOut.txt", "w") ) return -1;

    BubbleSort (hamletText.lines, 
                hamletText.numLines, 
                sizeof (String), 
                &CompDirectSorting);

    PrintLines (fileOut, hamletText.lines, hamletText.numLines);

    BubbleSort (hamletText.lines, 
                hamletText.numLines, 
                sizeof (String), 
                &CompReverseSorting);

    PrintLines (fileOut, hamletText.lines, hamletText.numLines);

    // Original
    PrintLines (fileOut, hamletTextCopy.lines, hamletTextCopy.numLines);

    /*
    qsort (hamletText.lines, 
           hamletText.numLines, 
           sizeof (String), 
           &CompDirectSorting);
    */

    QuickSort (hamletText.lines, 
               hamletText.numLines, 
               sizeof (String), 
               &CompDirectSorting);

    PrintLines (fileOut, hamletText.lines, hamletText.numLines);

    TextDestr (&hamletText);
    TextDestr (&hamletTextCopy);

    fclose (fileIn);
    fclose (fileOut);

    return 0;
}

//-----------------------------------------------------------------------------

int CompDirectSorting (const void * ptr_string1, const void * ptr_string2)
{
    //{ ASSERT
    assert (ptr_string1 != NULL);
    assert (ptr_string2 != NULL);
    //}
    
    const char * str1 = ((const String*)ptr_string1)->str;
    const char * str2 = ((const String*)ptr_string2)->str;
    
    int numLeftIgnSyms1 = ((const String*)ptr_string1)->numLeftIgnSyms;
    int numLeftIgnSyms2 = ((const String*)ptr_string2)->numLeftIgnSyms;
    
    return strcmp ( str1 + numLeftIgnSyms1, str2 + numLeftIgnSyms2 );
}

//-----------------------------------------------------------------------------

int CompReverseSorting (const void * ptr_string1, const void * ptr_string2)
{
    //{ ASSERT
    assert (ptr_string1 != NULL);
    assert (ptr_string2 != NULL);
    //}
    
    const char * str1 = ((const String*)ptr_string1)->str;
    const char * str2 = ((const String*)ptr_string2)->str;

    int lenStr1 = ((const String*)ptr_string1)->len;
    int lenStr2 = ((const String*)ptr_string2)->len;

    int numRightIgnSyms1 = ((const String*)ptr_string1)->numRightIgnSyms;
    int numRightIgnSyms2 = ((const String*)ptr_string2)->numRightIgnSyms;

    return StrReverseCmp ( str1, lenStr1 - numRightIgnSyms1, 
                           str2, lenStr2 - numRightIgnSyms2 );
}

//-----------------------------------------------------------------------------
