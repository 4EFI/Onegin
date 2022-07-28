#include "StringProcessing.h"

int main()
{
    const char* unitTests[] = {"Vlados\n",
                               "Sanya\n",
                               "Ded32\n",
                               "\n",
                               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab\n",
                               "0123456789012345678901234567890123456789012345678901234567890123#"};

    StrLen(nullptr);

    UnitTestsFGets(unitTests, sizeof(unitTests) / sizeof(char*), "UnitTests.txt");

    return 0;
}
