/*--------------- S e r I O D r i v e r . c ---------------

by: Kianush Aryan
    ECE Dept.
    UMASS Lowell

PURPOSE
The RS232 driver module, which defines the buffer pairs
iBfrPair and oBfrPair, and I/O driver functions
IntSerIO(), PutByte(), GetByte() as well as the two tasks
ServiceTx() and ServiceRx().

CHANGES
2-18-2018 ka   -  Added stubs and structures
2-24-2018 ka   -  Defined Buffer, BfrPair, SerIODriver routines
3-2-2018 ka    -  Add interrupt frame

*/
#include "SerIODriver.h"
#include <bsp.h>


#define USART_RXNE  0x20  // Rx not Empty Status Bit
#define USART_TXE   0x80  // Tx Empty Status Bit

/*----- g l o b a l   d e c l a r a t i o n s -----*/

// Allocate the input buffer pair.
static BfrPair iBfrPair;
static CPU_INT08U iBfr0Space[BfrSize];
static CPU_INT08U iBfr1Space[BfrSize];
// Allocate the output buffer pair.
static BfrPair oBfrPair;
static CPU_INT08U oBfr0Space[BfrSize];
static CPU_INT08U oBfr1Space[BfrSize];

/*----- f u n c t i o n     d e f i n i t i o n s -----*/

void InitSerIO(void)
{
  BfrPairInit(&iBfrPair, iBfr0Space, iBfr1Space, BfrSize);
  BfrPairInit(&oBfrPair, oBfr0Space, oBfr1Space, BfrSize);
  
  //todo: unmask the Rx and Tx interrupts
  
  //todo: Enable IRQ38(USART)
  
}

CPU_INT16S PutByte(CPU_INT16S txChar)
{
  if (BfrPairSwappable(&oBfrPair))
    BfrPairSwap(&oBfrPair);

  if (PutBfrClosed(&oBfrPair))
    return -1;

  if (PutBfrAddByte(&oBfrPair, txChar) == -1)
    return -1;
  else
    //todo: unmask Tx interrupt
    return txChar;
}
void ServiceTx()
{
    CPU_INT08U c;
    if(!(USART2->SR & USART_TXE))
    {
      return;                           //TXE = 0
    }
    else
    {
      if (GetBfrClosed(&oBfrPair))      //getBfr is not empty, OK to extract byte
      {
        c = GetBfrRemByte(&oBfrPair);
        USART2->DR = c;
        return;
      }
      else
      {
          //todo: mask the Tx and return
      }
    }
}


void ServiceRx(void)
{
    if(!(USART2->SR & USART_RXNE) | PutBfrClosed(&iBfrPair))
    {
      return;                           //RXNE = 0
    }

    PutBfrAddByte(&iBfrPair, USART2->DR);
    
    //if (PutBfrClosed(&iBfrPair))
    //todo: mask the Rx interrupt 
      
      
}

CPU_INT16S GetByte(void)
{
    if (BfrPairSwappable(&iBfrPair))
    BfrPairSwap(&iBfrPair);

    if (GetBfrClosed(&iBfrPair))
      //todo: unmask the Rx interrupt
      return GetBfrRemByte(&iBfrPair);
    else
      return -1;
}

void SerialISR()
{
      ServiceRx();
      ServiceTx();
      
}
