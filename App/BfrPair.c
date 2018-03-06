/*--------------- B f r P a i r . c ---------------

by: Kianush Aryan
    ECE Dept.
    UMASS Lowell

PURPOSE
Defines type “BfrPair” and associated functions.

CHANGES
2-18-2018 ka   -  Added stubs and structures
2-24-2018 ka   -  Defined Buffer, BfrPair, SerIODriver routines
*/

#include "BfrPair.h"

void BfrPairInit( BfrPair *bfrPair,
                  CPU_INT08U *bfr0Space,
                  CPU_INT08U *bfr1Space,
                  CPU_INT16U size)
{
  BfrInit(&bfrPair->buffers[0], bfr0Space,size); //buffer pair put buffer
  BfrInit(&bfrPair->buffers[1], bfr1Space,size); //buffer pair get buffer
}

void PutBfrReset(BfrPair *bfrPair)
{
  BfrReset(&bfrPair->buffers[bfrPair->putBfrNum]); //buffer pair put buffer
}

CPU_INT08U *PutBfrAddr(BfrPair *bfrPair)
{
  return (bfrPair->buffers[bfrPair->putBfrNum].buffer);  
}

CPU_INT08U *GetBfrAddr(BfrPair *bfrPair)
{
  return bfrPair->buffers[!bfrPair->putBfrNum].buffer;   
}

CPU_BOOLEAN PutBfrClosed(BfrPair *bfrPair)
{
  return BfrFull(&bfrPair->buffers[bfrPair->putBfrNum]);
}

CPU_BOOLEAN GetBfrClosed(BfrPair *bfrPair)
{
  return BfrClosed(&bfrPair->buffers[!bfrPair->putBfrNum]);
}

void ClosePutBfr(BfrPair *bfrPair)
{
  BfrClose(&bfrPair->buffers[bfrPair->putBfrNum]);
}

void OpenGetBfr(BfrPair *bfrPair)
{
  BfrOpen(&bfrPair->buffers[!bfrPair->putBfrNum]);
}

CPU_INT16S PutBfrAddByte(BfrPair *bfrPair, CPU_INT16S byte)
{
  if (BfrAddByte(&bfrPair->buffers[bfrPair->putBfrNum], byte) == byte)
    return byte;
  else
    return -1;

}

CPU_INT16S GetBfrRemByte(BfrPair *bfrPair)
{
  return BfrNextByte(&bfrPair->buffers[!bfrPair->putBfrNum]);
}

CPU_BOOLEAN BfrPairSwappable(BfrPair *bfrPair)
{
  if (PutBfrClosed(bfrPair) == TRUE)
  {
    if (GetBfrClosed(bfrPair) == FALSE)
    {
      //swaping buffers is possible
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
}

void BfrPairSwap(BfrPair *bfrPair){
  bfrPair->putBfrNum = !bfrPair->putBfrNum;             //toggle the put buffer address space pointer
  PutBfrReset(bfrPair);
}
