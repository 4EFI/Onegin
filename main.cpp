#include <string.h>

#include "StringProcessing.h"
#include "LOG/Log.h"

//-----------------------------------------------------------------------------

struct StrParams
{
    char* str = NULL;
    int   len = 0;
};

//-----------------------------------------------------------------------------

int GetFileStrs (FILE* file, StrParams arrStrs[]);

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

    char fileName[] = "Onegin.bin";

    FILE *file = fopen (fileName, "rb");

    if (file == NULL)
    {
        printf ("An error during opening file...\n");
    }

    StrParams* arrStrs = NULL;
    int numStrs = GetFileStrs (file, arrStrs);

    fclose (file);

    return 0;
}

//-----------------------------------------------------------------------------

int GetFileStrs (FILE* file, StrParams arrStrs[])
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (file != NULL);
    //}

    fseek (file, 0, SEEK_END);

    int fileSize = ftell (file);

    FLOG ("fileSize = %d", fileSize);

    char* str = (char*) calloc (sizeof (char), fileSize + 1);

    fseek (file, 0, SEEK_SET);

    int rightRead = fread (str, sizeof (char), fileSize, file);

    FLOG ("right read = %d",          rightRead);
    FLOG ("last str sym = '%c' = %d", str[fileSize], str[fileSize]);
    FLOG ("sizeof char ** = %d",      sizeof(char**));

    int numStrs = 0;

    for (int i = 0; i < fileSize; i++)
    {
        if (str[i] == '\n')
        {
            numStrs++;
        }
    }

    arrStrs = (StrParams*) calloc (sizeof (StrParams), numStrs);

    int pos = 0, nowStr = 0;

    for (int i = 0; i < fileSize; i++)
    {
        if (str[i] == '\n')
        {
            arrStrs[nowStr].str = &str[i - pos];
            //+1 for '\0'
            arrStrs[nowStr].len      = pos + 1;
            arrStrs[nowStr].str[pos]     = '\0';
            arrStrs[nowStr].str[pos - 1] = '\0';

            pos = 0;
            nowStr++;

            continue;
        }

        pos++;
    }

    for (int i = 0; i < numStrs; i++)
    {
        LOG ("%d) '%s'", i + 1, arrStrs[i].str);
    }

    return numStrs;
}

//-----------------------------------------------------------------------------

