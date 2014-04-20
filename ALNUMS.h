/*******************************************************************************
 * Store the so-called ALNUMS array in PROGMEM because it is really big.
 * Abstract away PROGMEM access formalities and store required bitmap in a
 * buffer.
 ******************************************************************************/
#ifndef _ALNUMS_H_
#define _ALNUMS_H_

#include "Arduino.h"
#include <avr/pgmspace.h>

extern byte ALNUMS[][5] PROGMEM;
extern byte bitmap[5];

// load bitmap array above with bitmap of parameter char
void load_bitmap(char l);

#endif // _ALNUMS_H_
