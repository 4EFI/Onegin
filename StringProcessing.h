#ifndef STRING_PROCESSING
#define STRING_PROCESSING

//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <algorithm>

//-----------------------------------------------------------------------------

const bool Debug = true;

int Line = 0;

char StrNullPtr[] = "Pointer cannot be null!";

//-----------------------------------------------------------------------------

#define LocCurSet() Line = __LINE__

#define Assert(condition, strFail) \
    if(!condition) \
    { \
        printf("Line %d: condition \"%s\" is failed!\n", Line, #condition); \
        printf("%s\n\n", strFail); \
    }

//-----------------------------------------------------------------------------

int   StrLen (const char* str);
void  Puts   (const char* str);
char* StrChr (      char* str,          char  symbol);
void  StrCpy (      char* str_to, const char* str_from);
void  StrNCpy(      char* str_to, const char* str_from, int n);
void  StrCat (      char* str_to, const char* str_from);
void  StrNCat(      char* str_to, const char* str_from, int n);
int   StrCmp (const char* str1,   const char* str2);

char* FGets(char *str, int n, FILE *file);

int UnitTestsFGets(const char* testStr[], int numUnitTests, const char* filePath);

//-----------------------------------------------------------------------------

int StrLen(const char* str)
{
    //{ ASSERT
    Assert(str != NULL, StrNullPtr);
    //}

    int i = 0;

    for ( ; str[i] != '\0'; i++) ;

    return i;
}

//-----------------------------------------------------------------------------

void Puts(const char* str)
{
    //{ ASSERT
    assert(str != NULL);
    //}

    int length = StrLen(str);

    for (int i = 0; i < length; i++)
    {
        putchar(str[i]);
    }

    putchar('\n');
}

//-----------------------------------------------------------------------------

char* StrChr(char* str, char symbol)
{
    //{ ASSERT
    assert(str != NULL);
    //}

    int length = StrLen(str);

    if (Debug) printf("%d: length = %d\n", __LINE__, length);

    for (int i = 0; i < length; i++)
    {
        if (str[i] == symbol)
        {
            return str + i;
        }
    }

    return nullptr;
}

//-----------------------------------------------------------------------------

void StrCpy(char* str_to, const char* str_from)
{
    //{ ASSERT
    assert(str_to   != NULL);
    assert(str_from != NULL);
    //}

    int lengthFrom = StrLen(str_from);

    for(int i = 0; i <= lengthFrom; i++)
    {
        str_to[i + 1] = str_from[i];
    }
}

//-----------------------------------------------------------------------------

void StrNCpy(char* str_to, const char* str_from, int n)
{
    //{ ASSERT
    assert(str_to   != NULL);
    assert(str_from != NULL);
    //}

    int lengthFrom = StrLen(str_from);

    int minLen = std::min(lengthFrom, n);

    for (int i = 0; i < minLen; i++)
    {
        assert(0 <= i && i < n);

        str_to[i] = str_from[i];
    }

    for (int i = minLen; i < n; i++)
    {
        str_to[i] = '\0';
    }
}

//-----------------------------------------------------------------------------

void StrCat(char* str_to, const char* str_from)
{
    //{ ASSERT
    assert(str_to   != NULL);
    assert(str_from != NULL);
    //}

    int lengthTo = StrLen(str_to);

    StrCpy(str_to + lengthTo, str_from);
}

//-----------------------------------------------------------------------------

void StrNCat(char* str_to, const char* str_from, int n)
{
    //{ ASSERT
    assert(str_to   != NULL);
    assert(str_from != NULL);
    //}

    int lengthTo = StrLen(str_to);

    StrNCpy(str_to + lengthTo, str_from, n);
}

//-----------------------------------------------------------------------------

int StrCmp(const char* str1, const char* str2)
{
    //{ ASSERT
    assert(str1 != NULL);
    assert(str2 != NULL);
    //}

    for (int i = 0; ; i++)
    {
        if      (str1[i] > str2[i]) return  1;
        else if (str1[i] < str2[i]) return -1;

        if (str1[i] == '\0') return 0;
    }

    return 0;
}

//-----------------------------------------------------------------------------

char* FGets(char *str, int n, FILE *file)
{
    //{ ASSERT
    assert(str  != NULL);
    assert(file != NULL);
    //}

    if (file == NULL) return nullptr;

    for (int i = 0; i < n - 1; i++)
    {
        int sym = getc(file);

        switch(sym)
        {
            case EOF:
            {
                return ( i == 0 ? nullptr : (str[i] = '\0', str) );
            }
            case '\n':
            {
                str[i]     = '\n';
                str[i + 1] = '\0';

                return str;
            }
            default:
            {
                str[i] = sym;
            }
        }
    }

    str[n - 1] = '\0';

    return str;
}

//-----------------------------------------------------------------------------

int UnitTestsFGets(const char* testStr[], int numUnitTests, const char* filePath)
{
    //{ ASSERT
    assert(testStr  != NULL);
    assert(filePath != NULL);
    //}

    bool isError = false;

    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        printf("File does not exist!\n");

        return -1;
    }

    for (int i = 0; i < numUnitTests; i++)
    {
        char str[100] = "";

        FGets(str, sizeof(str), file);

        if (strcmp(str, testStr[i]) != 0)
        {
            printf("Test number %d: should be \"%s\"; program solution is \"%s\"\n", i,
                   testStr[i], str);
        }
        else
        {
            printf("Test number %d have passed\n", i);
        }
    }

    fclose(file);

    return isError;
}

//  Redefinition functions
//{----------------------------------------------------------------------------

#define StrLen(...) ( LocCurSet(), StrLen(__VA_ARGS__) )

//}----------------------------------------------------------------------------

#endif
