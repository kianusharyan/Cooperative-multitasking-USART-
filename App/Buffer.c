/*--------------- B u f f e r . c ---------------

by: Kianush Aryan
    ECE Dept.
    UMASS Lowell

PURPOSE
Required Buffer Data type and functions.

CHANGES
2-18-2018 ka   -  Added stubs and structures
2-24-2018 ka   -  Defined Buffer, BfrPair, SerIODriver routines

*/

/*----- c o n s t a n t    d e f i n i t i o n s -----*/

/*----- f u n c t i o n    p r o t o t y p e s -----*/

#include "Buffer.h"

/*----- f u n c t i o n     d e f i n i t i o n s -----*/

/*
PURPOSE
Initialize a buffer: record the size, set putIndex and
getIndex to zero, and mark the buffer open.
*/
void BfrInit( Buffer *bfr, CPU_INT08U *bfrSpace, CPU_INT16U size)
{
  bfr->size = size;
  bfr->putIndex = 0;
  bfr->getIndex = 0;
  bfr->buffer = bfrSpace;
  bfr->closed = FALSE;
}
/*
PURPOSE
Reset the buffer: set putIndex and getIndex to
zero, and mark the buffer open.
*/
void BfrReset(Buffer *bfr)
{
  bfr->putIndex = 0;
  bfr->getIndex = 0;
  bfr->closed = FALSE;
}

/*
PURPOSE
Test whether a buffer is closed or not.
*/
CPU_BOOLEAN BfrClosed(Buffer *bfr)
{
  return bfr->closed;
}

/*
PURPOSE
Mark the buffer closed.
*/
void BfrClose(Buffer *bfr)
{
  bfr->closed = TRUE;
}

/*
PURPOSE
Mark the buffer open.
*/
void BfrOpen(Buffer *bfr)
{
  bfr->closed = FALSE;
}

/*
PURPOSE
Test whether or not a
buffer is full.
*/
CPU_BOOLEAN BfrFull(Buffer *bfr)
{
  return (bfr->putIndex >= bfr->size);              
}

/*
PURPOSE
Test whether or not a
buffer is empty.
*/
CPU_BOOLEAN BfrEmpty(Buffer *bfr)
{
  return (bfr->putIndex <= bfr->getIndex);            
}

/*
PURPOSE
Add a byte to a buffer at position “putIndex” and
increment “putIndex” by 1. If the buffer becomes full,
mark it closed.
*/
CPU_INT16S BfrAddByte(Buffer *bfr,
                      CPU_INT16S theByte)
{
  if(BfrFull(bfr))
    return -1;

  bfr->buffer[bfr->putIndex++] = theByte;
  if(BfrFull(bfr))
    BfrClose(bfr);
  return theByte;
}

/*
PURPOSE
Return the byte from position “getIndex” or
return -1 if the buffer is empty.
*/
CPU_INT16S BfrNextByte(Buffer *bfr)
{
  if(BfrEmpty(bfr))
    return -1;
  else
    return BfrRemByte(bfr);
}

/*
PURPOSE
Return the byte from position “getIndex” and
increment “getIndex” by 1.
If the buffer becomes empty, mark it open.
*/
CPU_INT16S BfrRemByte(Buffer *bfr)
{
  CPU_INT16S theByte;
  theByte = bfr->buffer[bfr->getIndex++];

  if(BfrEmpty(bfr))
    BfrOpen(bfr);
  
  return theByte;
}
