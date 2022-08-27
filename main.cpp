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

    char* str = NULL;

    int strSize = GetFileStr (file, &str);

    StrParams* arrStrs = NULL;
    int numStrs = DivideStr (str, &arrStrs);

    for (int i = 0; i < numStrs; i++)
    {
        LOG ("%d) '%s'", i + 1, arrStrs[i].str);
    }

    for (int i = 0; i < numStrs; i++)
    {
        RemoveIgnoredSyms (&arrStrs[i].str, 0,                  arrStrs[i].len - 1);
        RemoveIgnoredSyms (&arrStrs[i].str, arrStrs[i].len - 1, 0);
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


