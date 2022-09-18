#include <string.h>

#include "StringProcessing.h"
#include "FileAlgorithms.h"
#include "StrAlgorithms.h"
#include "Comparators.h"
#include "LOG.h"

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