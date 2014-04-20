#ifndef INTELHEX_H
#define INTELHEX_H
#include <stdint.h>

/* This is not suitable as a generic intel hex data formatting tool */

void write_ihex(FILE *file, uint8_t *data, int len, uint16_t relative_address);

#endif
