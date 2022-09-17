#ifndef STR_ALGORITHM_H
#define STR_ALGORITHM_H

#include <stdio.h>

//-----------------------------------------------------------------------------

struct String
{
    char* str;
    int   len;
};

//-----------------------------------------------------------------------------

struct Text
{
private:
    FILE * file;
    
    char * allStr;
    long int strSize;

    String * lines;
    long int numLines;

    long int SetStr();

public:
    Text() {file = stdin, allStr = NULL, strSize = 0, lines = NULL, numLines = 0;}
    
    bool     SetFile (const char * fileName, const char * typeOpen = "r");
    long int SetLines();

    String * GetLines   () { return lines;    }
    long int GetNumLines() { return numLines; }
};

//-----------------------------------------------------------------------------

const char IgnoredSymbols[] = " .,()[]{}<>\\/|~`!?:;-'";

//-----------------------------------------------------------------------------

int DivideStr (char* str, String** arrStrs);

int GetNumStrs (const char *str);

int TrimLeftIgnoredSyms  (char** str, const char *ignoredSymbols = IgnoredSymbols);
int TrimRightIgnoredSyms (char** str, const char *ignoredSymbols = IgnoredSymbols);

void TrimStrings (String arrStrs[], int numStrs, const char *ignoredSymbols = IgnoredSymbols);

int RemoveIgnoredSyms (char** str, int iBegin, int iEnd);

void BubbleSort (void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2));
void QuickSort  (void * arr, size_t num, size_t size, int (*comparator)(const void * arr1, const void * arr2));

void Swap (void * a, void * b, size_t size);

void CopyLines (String strTo[], const String strFrom[], int numLines);

void PrintLines (FILE* file, String* arrStrs, int numLines);

//-----------------------------------------------------------------------------

#endif
