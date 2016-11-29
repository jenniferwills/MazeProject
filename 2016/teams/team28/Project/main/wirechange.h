#ifndef WIRECHANGE_H_INCLUDED
#define WIRECHANGE_H_INCLUDED

#include <Wire.h>

void WireInit();
void WireWrite(int address, uint8_t value);
void WireWriteTwo(int address, uint8_t value, uint8_t value2);
void GetValueArray(int address, uint32_t *ValArray, uint8_t len);

#endif

