#include <stdint.h>
#include <string.h>
#include "upgrade.h"

uint8_t *create_header(uint8_t key_name, uint8_t major_version, uint8_t minor_version, uint8_t hardware_revision, uint8_t pages, int *length) {
	const uint8_t base[] = {
		0x80, 0x0F, 0x00, 0x00, 0x00, 0x00,
		0x80, 0x11, 0x00, // Key
		0x80, 0x21, 0x00, // Major version
		0x80, 0x32, 0x00, // Minor version
		0x80, 0xA1, 0x00, // Hardware revision
		0x80, 0x81, 0x00, // Pages
		0x80, 0x7F, 0x00, 0x00, 0x00, 0x00
	};
	uint8_t *header = malloc(sizeof(base));
	memcpy(header, base, sizeof(base));
	header[8] = key_name;
	header[11] = major_version;
	header[14] = minor_version;
	header[17] = hardware_revision;
	header[20] = pages;
	*length = sizeof(base);
	return header;
}
