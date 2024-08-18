#include <stdio.h>
#include "log.c"
#include "heap.c"

int main()
{
    logInit();
    
    heapInit();
    logExit();
    //char* heapBuf = heapMalloc(32);
}