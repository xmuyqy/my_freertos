#include <stdio.h>
#include "log.c"
#include "heap.c"

int main()
{
    logInit();
    
    heapInit();
    
    char* heapBuf = heapMalloc(32);

    logExit();
}