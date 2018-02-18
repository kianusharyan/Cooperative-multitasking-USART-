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

*/
#pragma once
#include "SerIODriver.h"

/*----- g l o b a l   d e c l a r a t i o n s -----*/

// Allocate the input buffer pair.
static BfrPair iBfrPair;
static CPU_INT08U iBfr0Space[BfrSize];
static CPU_INT08U iBfr1Space[BfrSize];
// Allocate the output buffer pair.
static BfrPair oBfrPair;
static CPU_INT08U oBfr0Space[BfrSize];
static CPU_INT08U oBfr1Space[BfrSize];
