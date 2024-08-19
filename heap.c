#pragma once

#include <stdio.h>
#include <stdint.h>
#include "log.c"
#define PORT_BYTE_ALIGNMENT 8
#define PORT_BYTE_ALIGNMENT_MASK (0x0007)
#define TOTAL_HEAP_SIZE 1024
#define ADJUST_TOTAL_HEAP_SIZE (TOTAL_HEAP_SIZE - PORT_BYTE_ALIGNMENT)

static uint8_t myHeap[TOTAL_HEAP_SIZE];
static uint8_t *heapStartAddr = NULL;
static uint32_t curExpendByte = 0; //  

void heapInit()
{
    /* 对堆的首地址进行对齐 */
    heapStartAddr = (uint8_t *) (((uint32_t) &myHeap[PORT_BYTE_ALIGNMENT]) & (~((uint32_t) PORT_BYTE_ALIGNMENT_MASK)));
    debug("debug info: free byte: %d\n", ADJUST_TOTAL_HEAP_SIZE - curExpendByte);
}

void *heapMalloc(uint32_t wantedSize) 
{
    void *pReturn = heapStartAddr + curExpendByte;

    /* 对wantedSize进行对齐 */
    if(wantedSize & PORT_BYTE_ALIGNMENT_MASK) {
        wantedSize += PORT_BYTE_ALIGNMENT - (wantedSize & PORT_BYTE_ALIGNMENT_MASK);
    }

    /* 检查heap空间还够不够以及防溢出 */
    if(((curExpendByte + wantedSize) < ADJUST_TOTAL_HEAP_SIZE) &&
        ((curExpendByte + wantedSize) > curExpendByte)) {   
        curExpendByte += wantedSize;
    }

    debug("debug info: allocate byte: %d, free byte: %d\n", wantedSize, ADJUST_TOTAL_HEAP_SIZE - curExpendByte);
    return pReturn;
}
