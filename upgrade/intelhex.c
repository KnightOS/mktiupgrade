#include <stdint.h>
#include <stdio.h>
#include "intelhex.h"

#define BYTES_PER_PAGE 32

/* This is not suitable as a generic intel hex data formatting tool */

void write_ihex(FILE *file, uint8_t *data, int len, uint16_t relative_address) {
	int i;
	for (i = 0; i < len; i += BYTES_PER_PAGE) {
		uint16_t address = i + relative_address;
		if (relative_address == 0xFFFF) {
			address = 0;
		}
		uint8_t checksum = 0;
		uint8_t record_type = 0;
		uint8_t bytes = BYTES_PER_PAGE;
		if (len - i < BYTES_PER_PAGE) {
			bytes = len - i;
		}
		checksum += bytes;
		checksum += address & 0xFF;
		checksum += (address >> 8) & 0xFF;
		fprintf(file, ":%02X%04X%02X", bytes, address, record_type);
		int j;
		for (j = 0; j < bytes; j++) {
			checksum += data[j];
			fprintf(file, "%02X", data[j]);
		}
		checksum = 0x100 - checksum;
		fprintf(file, "%02X\r\n", checksum);
		data += bytes;
	}
}
