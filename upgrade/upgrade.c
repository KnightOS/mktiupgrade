#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include "devices.h"
#include "intelhex.h"
#include "upgrade.h"

uint8_t *create_header(uint8_t key_name, uint8_t major_version, uint8_t minor_version, uint8_t hardware_revision, uint8_t pages, int *length) {
	/* TODO: Write the header properly, not hardcoded */
	const uint8_t base[] = {
		0x80, 0x0F, 0x00, 0x00, 0x00, 0x00,
		0x80, 0x11, 0x00, // Key
		0x80, 0x21, 0x00, // Major version
		0x80, 0x31, 0x00, // Minor version
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

void write_upgrade(FILE *file, device_type_t device, int pages[256], uint8_t *os_header, int header_len, uint8_t *os_data, int os_len, uint8_t *signature, int sig_len) {
	/* Header */
	write_flash_header(file, device);
	uint32_t l = ftell(file);
	write_ihex(file, os_header, header_len, 0);
	fprintf(file, ":00000001FF\r\n");
	/* OS */
	int i, j = 0;
	for (i = 0; i < os_len / 0x4000; i++) {
		while (!pages[j]) j++;
		fprintf(file, ":0200000200%02X%02X\r\n", j, 0xFC - j);
		if (i == 0) {
			write_ihex(file, os_data + (i * 0x4000), 0x4000, 0);
		} else {
			write_ihex(file, os_data + (i * 0x4000), 0x4000, 0x4000);
		}
		j++;
	}
	fprintf(file, ":00000001FF\r\n");
	/* Signature */
	write_ihex(file, signature, sig_len, -1);
	fprintf(file, ":00000001FF  -- CONVERT 2.6 --\r\n");
	/* Length */
	uint32_t chars = ftell(file) - l;
	fflush(file);
	fseek(file, l - sizeof(uint32_t), SEEK_SET);
	fwrite(&chars, sizeof(uint32_t), 1, file);
	fseek(file, 0, SEEK_END);
}

void write_flash_header(FILE *file, device_type_t device) {
	const uint8_t revision[] = { 0x02, 0x40 };
	const uint8_t flags[] = { 0x01 };
	const uint8_t object_type[] = { 0x88 };
	const uint8_t date[] = { 0x11, 0x26, 0x20, 0x07 }; /* Set to 2014-04-19 because no one cares */
	const uint8_t namelen = 8;
	const uint8_t type = device == TI73 ? 0x74 : 0x73;
	const uint8_t data_type = 0x23; /* For OS types */
	const uint32_t ihlen = 0; /* Filled out at the end */
	uint8_t nulls[24];
	memset(nulls, 0, sizeof(nulls));

	fprintf(file, "%s", "**TIFL**");
	fwrite(revision, sizeof(uint8_t), sizeof(revision), file);
	fwrite(flags, sizeof(uint8_t), sizeof(flags), file);
	fwrite(object_type, sizeof(uint8_t), sizeof(object_type), file);
	fwrite(date, sizeof(uint8_t), sizeof(date), file);
	fwrite(&namelen, sizeof(uint8_t), 1, file);
	fprintf(file, "%s", "basecode");
	fwrite(nulls, sizeof(uint8_t), 23, file);
	fwrite(&type, sizeof(uint8_t), 1, file);
	fwrite(&data_type, sizeof(uint8_t), 1, file);
	fwrite(nulls, sizeof(uint8_t), 24, file);
	fwrite(&ihlen, sizeof(uint32_t), 1, file);
}
