#include <string.h>

#include "../include/StringProcessing.h"
#include "../include/StrAlgorithm.h"
#include "../LOG/LOG.h"

//-----------------------------------------------------------------------------

int main()
{
    printf ("hh\n");

    /* Unit tests
    const char* unitTests[] = {"Vlados\n",
                               "Sanya\n",
                               "Ded32\n",
                               "\n",
                               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\n",
                               "0123456789012345678901234567890123456789012345678901234567890123#"};


    UnitTestsFGets(unitTests, sizeof(unitTests) / sizeof(char*), "UnitTests.txt");
    */

    char fileName[] = "Hamlet.txt";

    FILE *file = fopen (fileName, "r");

    if (!file)
    {
        printf ("An error during opening file...\n");
    }

    char* str = NULL;

    ReadAllFile (file, &str);

    StrParams* arrStrs = NULL;
    int numStrs = DivideStr (str, &arrStrs);

    TrimStrings (arrStrs, numStrs);

    BubbleSortStrings (arrStrs, numStrs);

    FILE* fileOut = fopen ("_.txt", "w");

    // print_lines()
    for (int i = 0; i < numStrs; i++)
    {
        fprintf (fileOut, "%d) '%s'\n", i + 1, arrStrs[i].str);
    }

    fclose (file);

    return 0;
}

//-----------------------------------------------------------------------------


