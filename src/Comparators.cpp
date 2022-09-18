#include "Comparators.h"
#include "StrAlgorithms.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------

int CompDirectSorting (const void * ptr_string1, const void * ptr_string2)
{
    //{ ASSERT
    assert (ptr_string1 != NULL);
    assert (ptr_string2 != NULL);
    //}
    
    const char * str1 = ((const String*)ptr_string1)->str;
    const char * str2 = ((const String*)ptr_string2)->str;
    
    int numLeftIgnSyms1 = ((const String*)ptr_string1)->numLeftIgnSyms;
    int numLeftIgnSyms2 = ((const String*)ptr_string2)->numLeftIgnSyms;
    
    return strcmp ( str1 + numLeftIgnSyms1, str2 + numLeftIgnSyms2 );
}

//-----------------------------------------------------------------------------

int CompReverseSorting (const void * ptr_string1, const void * ptr_string2)
{
    //{ ASSERT
    assert (ptr_string1 != NULL);
    assert (ptr_string2 != NULL);
    //}
    
    const char * str1 = ((const String*)ptr_string1)->str;
    const char * str2 = ((const String*)ptr_string2)->str;

    int lenStr1 = ((const String*)ptr_string1)->len;
    int lenStr2 = ((const String*)ptr_string2)->len;

    int numRightIgnSyms1 = ((const String*)ptr_string1)->numRightIgnSyms;
    int numRightIgnSyms2 = ((const String*)ptr_string2)->numRightIgnSyms;

    return StrReverseCmp ( str1, lenStr1 - numRightIgnSyms1, 
                           str2, lenStr2 - numRightIgnSyms2 );
}

//-----------------------------------------------------------------------------
