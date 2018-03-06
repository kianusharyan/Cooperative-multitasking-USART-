/*--------------- S e r I O D r i v e r . h ---------------

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
3-2-2018 ka    -  Add interrupt frame

*/
#pragma once
#include "includes.h"
#include "BfrPair.h"

/*----- c o n s t a n t    d e f i n i t i o n s -----*/

// If not already defined, use the default buffer size of 4.
#ifndef BfrSize
#define BfrSize 4
#endif

/*----- f u n c t i o n    p r o t o t y p e s -----*/

/*
PURPOSE
Initialize the RS232 I/O driver by initializing both iBfrPair and
oBfrPair. Unmask Tx and Rx interrupts, and enable IRQ38.

PARAMETERS: VOID

RETURN VALUE: VOID
*/
void InitSerIO(void);

/*
PURPOSE: 
If the oBfrPair put buffer is closed and the oBfrPair get buffer is not
closed, swap the get buffer and put buffer.
If the oBfrPair put buffer is not full, write one byte into the buffer, unmask Tx, and
return txChar as the return value; if, the buffer is full, return -1 indicating
failure.

PARAMETERS: the data byte to be trasmitted

RETURN VALUE:
On success, PutByte() returns the character in
“txChar” that was added to the put buffer. If the put
buffer is already full, txChar returns –1 to indicate
failure.
*/
CPU_INT16S PutByte(CPU_INT16S txChar);


/*
PURPOSE
If TXE = 1 and the oBfrPair get buffer is not empty, then output one
byte to the UART Tx and return. If TXE = 0 or if the get buffer is
empty, just return. If the get buffer is not closed mask the Tx and return.

PARAMETERS: VOID

RETURN VALUE: VOID
*/
void ServiceTx(void);

/*
PURPOSE: 
If the iBfrPair put buffer is closed and the iBfrPair get buffer is not
closed, unmask Rx interrupt, swap the get buffer and put
buffer.
If the iBfrPair get buffer is not empty, remove and return the next
byte from the buffer. if the buffer is empty, return -1 indicating failure

PARAMETERS: VOID

RETURN VALUE: On success, GetByte() returns the character read
from get buffer. If the get buffer is empty, GetByte()
returns –1 to indicate failure.

*/
CPU_INT16S GetByte(void);

/*
PURPOSE
If RXNE = 1 and the iBfrPair put buffer is not full, then read a byte
from the UART Rx and add it to the put buffer. If RXNE = 0 or the put
buffer is full, just return.If the put buffer is closed, mask the
Rx interrupt and return.

PARAMETERS: VOID

RETURN VALUE: VOID
*/
void ServiceRx(void);

/*
PURPOSE
Call ServiceRx() to handle Rx interrupts and then call ServiceTx()
to handle Tx interrupts.

PARAMETERS: VOID

RETURN VALUE: VOID
*/

void SerialISR(void);
