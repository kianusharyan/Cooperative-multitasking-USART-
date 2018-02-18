/*--------------- B u f f e r . h ---------------

by: Kianush Aryan
    ECE Dept.
    UMASS Lowell

PURPOSE
Required Buffer Data type properties and function prototypes.


CHANGES
2-18-2018 ka   -  Added stubs and structures

*/

#pragma once
#include "includes.h"


/*----- s t r u c t    d e f i n i t i o n s -----*/

typedef struct
{
    CPU_BOOLEAN closed; /* -- True if buffer has data ready to process, ready to be emptied or being emptied */
    /* -- False if buffer is not ready to process, ready to fill or being filled */
    CPU_INT16U size; /* -- The capacity of the buffer in bytes */
    CPU_INT16U putIndex; /* -- The position where the next byte is added */
    CPU_INT16U getIndex; /* -- The position of the next byte to remove */
    CPU_INT08U *buffer; /* -- The address of the buffer data space */
} Buffer;


/*----- f u n c t i o n    p r o t o t y p e s -----*/

/*
PURPOSE
Initialize a buffer: record the size, set putIndex and
getIndex to zero, and mark the buffer open.
*/
void BfrInit( Buffer *bfr,
              CPU_INT08U *bfrSpace,
              CPU_INT16U size);
/*
PURPOSE
Reset the buffer: set putIndex and getIndex to
zero, and mark the buffer open.
*/
void BfrReset(Buffer *bfr);

/*
PURPOSE
Test whether a buffer is closed or not.
*/
CPU_BOOLEAN BfrClosed(Buffer *bfr);

/*
PURPOSE
Mark the buffer closed.
*/
void BfrClose(Buffer *bfr);

/*
PURPOSE
Mark the buffer open.
*/
void BfrOpen(Buffer *bfr);

/*
PURPOSE
Test whether or not a
buffer is full.
*/
CPU_BOOLEAN BfrFull(Buffer *bfr);

/*
PURPOSE
Test whether or not a
buffer is empty.
*/
CPU_BOOLEAN BfrEmpty(Buffer *bfr);

/*
PURPOSE
Add a byte to a buffer at position “putIndex” and
increment “putIndex” by 1. If the buffer becomes full,
mark it closed.
*/
CPU_INT16S BfrAddByte(Buffer *bfr,
                      CPU_INT16S theByte);

/*
PURPOSE
Return the byte from position “getIndex” or
return -1 if the buffer is empty.
*/
CPU_INT16S BfrNextByte(Buffer *bfr);

/*
PURPOSE
Return the byte from position “getIndex” and
increment “getIndex” by 1.
If the buffer becomes empty, mark it open.
*/
CPU_INT16S BfrRemByte(Buffer *bfr);
