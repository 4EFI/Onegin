#include <string.h>

#include "StringProcessing.h"
#include "LOG/Log.h"

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

    fseek (file, 0, SEEK_END);

    int fileSize = ftell (file);

    FLOG ("fileSize = %d", fileSize);

    char* str = (char*) malloc (fileSize);

    fread (str, sizeof (char), fileSize, file);

    printf ("'%s'", str);

    for (int i = 0; i < fileSize; i++)
    {

    }

    fclose (file);

    return 0;
}