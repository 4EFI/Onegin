#include <string.h>

#include "StringProcessing.h"
#include "StrAlgorithm.h"
#include "Log.h"

//-----------------------------------------------------------------------------

int main()
{
    const char* unitTests[] = {"Vlados\n",
                               "Sanya\n",
                               "Ded32\n",
                               "\n",
                               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\n",
                               "0123456789012345678901234567890123456789012345678901234567890123#"};


    //UnitTestsFGets(unitTests, sizeof(unitTests) / sizeof(char*), "UnitTests.txt");

    char fileName[] = "Onegin.txt";

    FILE *file = fopen (fileName, "r");

    if (!file)
    {
        printf ("An error during opening file...\n");
    }

    StrParams* arrStrs = NULL;
    int numStrs = GetFileStrs (file, &arrStrs);

    FLOG ("number of strings = %d", numStrs);

    for (int i = 0; i < numStrs; i++)
    {
        RemoveLeadingSpaces (&(arrStrs[i].str), arrStrs[i].len);
    }

    BubbleSortStrings (&arrStrs, numStrs);

    for (int i = 0; i < numStrs; i++)
    {
        LOG ("%d) '%s'", i + 1, arrStrs[i].str);
    }

    fclose (file);

    return 0;
}

//-----------------------------------------------------------------------------


