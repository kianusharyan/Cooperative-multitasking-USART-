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


void BfrInit( Buffer *bfr, CPU_INT08U *bfrSpace, CPU_INT16U size)
{
  bfr->size = size;
  bfr->putIndex = 0;
  bfr->getIndex = 0;
  bfr->buffer = bfrSpace;
  bfr->closed = FALSE;
}

void BfrReset(Buffer *bfr)
{
  bfr->putIndex = 0;
  bfr->getIndex = 0;
  bfr->closed = FALSE;
}


CPU_BOOLEAN BfrClosed(Buffer *bfr)
{
  return bfr->closed;
}


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


CPU_BOOLEAN BfrFull(Buffer *bfr)
{
  return (bfr->putIndex >= bfr->size);
}

CPU_BOOLEAN BfrEmpty(Buffer *bfr)
{
  return (bfr->putIndex <= bfr->getIndex);
}

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

CPU_INT16S BfrNextByte(Buffer *bfr)
{
  if(BfrEmpty(bfr))
    return -1;
  else
    return BfrRemByte(bfr);
}

CPU_INT16S BfrRemByte(Buffer *bfr)
{
  CPU_INT16S theByte;
  theByte = bfr->buffer[bfr->getIndex++];

  if(BfrEmpty(bfr))
    BfrOpen(bfr);

  return theByte;
}
