/*--------------- B f r P a i r . h ---------------

by: Kianush Aryan
    ECE Dept.
    UMASS Lowell

PURPOSE
Defines type “BfrPair” and associated functions.

CHANGES
2-18-2018 ka   -  Added stubs and structures

*/

#pragma once
#include "includes.h"
#include "Buffer.h"

/*----- c o n s t a n t    d e f i n i t i o n s -----*/

#define NumBfrs 2

/*----- s t r u c t    d e f i n i t i o n s -----*/

typedef struct
{
CPU_INT08U putBfrNum; /* -- The index of the put buffer */
Buffer buffers[NumBfrs]; /* -- The 2 buffers */
} BfrPair;

/*----- f u n c t i o n    p r o t o t y p e s -----*/


/*
PURPOSE
Initialize both buffers of the buffer pair.

PARAMETERS:
buffer pair address,
address of buffer 0 space,
address of buffer 1 space,
buffer capacity in bytes

RETURN VALUE: VOID
*/

void BfrPairInit( BfrPair *bfrPair,
                  CPU_INT08U *bfr0Space,
                  CPU_INT08U *bfr1Space,
                  CPU_INT16U size);


/*
PURPOSE
Reset the put buffer.

PARAMETERS:
buffer pair address

RETURN VALUE: VOID
*/
void PutBfrReset(BfrPair *bfrPair);

/*
PURPOSE
Obtain the address of the put buffer’s buffer data
space.

PARAMETERS:
buffer pair address

RETURN VALUE: The address of the put buffer’s buffer
data space
*/
CPU_INT08U *PutBfrAddr(BfrPair *bfrPair);

/*
PURPOSE
Obtain the address of the get buffer’s buffer data
space.

PARAMETERS:
buffer pair address

RETURN VALUE: The address of the get buffer’s buffer
data space
*/
CPU_INT08U *GetBfrAddr(BfrPair *bfrPair);

/*
PURPOSE
Test whether or not the put buffer is closed.

PARAMETERS:
buffer pair address

RETURN VALUE: TRUE if the put buffer is closed,
otherwise FALSE
*/
CPU_BOOLEAN PutBfrClosed(BfrPair *bfrPair);


/*
PURPOSE
Test whether or not the get buffer is closed.

PARAMETERS:
buffer pair address

RETURN VALUE:
buffer pair address TRUE if the get
*/
CPU_BOOLEAN GetBfrClosed(BfrPair *bfrPair);

/*
PURPOSE
Mark the put buffer
closed.

PARAMETERS:
buffer pair address

RETURN VALUE: NONE
*/
void ClosePutBfr(BfrPair *bfrPair);

/*
PURPOSE
Mark the get buffer open.

PARAMETERS:
buffer pair address

RETURN VALUE: NONE
*/
void OpenGetBfr (BfrPair *bfrPair);

/*
PURPOSE
Add a byte to the put buffer at position
“putIndex” and increment “putIndex” by 1. If the
buffer becomes full, mark it closed.

PARAMETERS:
buffer pair address,
the byte to be added

RETURN VALUE:
The byte added, unless the buffer
was full. If the buffer was full,
return -1.

*/
CPU_INT16S PutBfrAddByte(BfrPair *bfrPair,
                         CPU_INT16S byte);

/*
PURPOSE
Return the byte from position “getIndex” of the
get buffer or return -1 if the get buffer is empty.

PARAMETERS:
buffer pair address

RETURN VALUE:
The byte from position “getIndex”
of the get buffer unless the get buffer is empty. If
the buffer is empty, return -1.
*/
CPU_INT16S GetBfrNextByte(BfrPair *bfrPair);

/*
PURPOSE
Return the byte from position “getIndex” in the
get buffer and increment the get buffer’s
“getIndex” by 1. If the buffer becomes empty, mark
it open.

PARAMETERS:
buffer pair address

RETURN VALUE:
The byte from position “getIndex”
of the get buffer unless the get
buffer is empty. If the get buffer is
empty, return -1
*/
CPU_INT16S GetBfrRemByte(BfrPair *bfrPair);

/*
PURPOSE
Test whether or not a buffer pair is ready to be
swapped. It is ready if the put buffer is closed
and the get buffer is open

PARAMETERS:
buffer pair address

RETURN VALUE:
TRUE if ready to swap, otherwise FALSE
*/
CPU_BOOLEAN BfrPairSwappable(BfrPair *bfrPair);

/*
PURPOSE
Swap the put buffer and the get buffer, and reset
the put buffer.

PARAMETERS:
buffer pair address

RETURN VALUE: NONE
*/
void BfrPairSwap(BfrPair *bfrPair);
