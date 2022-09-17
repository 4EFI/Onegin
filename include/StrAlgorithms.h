#ifndef STR_ALGORITHM_H
#define STR_ALGORITHM_H

#include <stdio.h>

//-----------------------------------------------------------------------------

struct String
{
    char* str;
    int   len;

    int numLeftIgnSyms;
    int numRightIgnSyms;
};

//-----------------------------------------------------------------------------

struct Text
{
private:
    char * allStr;
    long int strSize;

public:
    String * lines;
    long int numLines; 

     Text() {allStr = NULL, strSize = 0, lines = NULL, numLines = 0;}
    ~Text();

    long int SetLines(FILE* file);
};

//-----------------------------------------------------------------------------

const char IgnoredSymbols[] = " .,()[]{}<>\\/|~`!?:;-'";

//-----------------------------------------------------------------------------

int DivideStr (char* str, String** arrStrs);

int GetNumStrs (const char *str);

int NumLeftIgnoredSyms  (const char* str, const char *ignoredSymbols = IgnoredSymbols);
int NumRightIgnoredSyms (const char* str, const char *ignoredSymbols = IgnoredSymbols);

int TrimLeftIgnoredSyms  (char** str, const char *ignoredSymbols = IgnoredSymbols);
int TrimRightIgnoredSyms (char** str, const char *ignoredSymbols = IgnoredSymbols);

void TrimStrings (String arrStrs[], int numStrs, const char *ignoredSymbols = IgnoredSymbols);

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd);

void BubbleSort (void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2));
void QuickSort  (void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2));

void Swap (void * a, void * b, size_t size);

void CopyLines (String** strTo, const String* strFrom, int numLines);

void PrintLines (FILE* file, String* arrStrs, int numLines);

int StrReverseCmp (const char* str1, size_t len1, const char* str2, size_t len2);

//-----------------------------------------------------------------------------

#endif
