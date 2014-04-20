#ifndef UPGRADE_H
#define UPGRADE_H
#include "devices.h"

uint8_t *create_header(uint8_t key_name, uint8_t major_version, uint8_t minor_version, uint8_t hardware_revision, uint8_t pages, int *length);
void write_upgrade(FILE *file, device_type_t device, int pages[256], uint8_t *os_header, int header_len, uint8_t *os_data, int os_len, uint8_t *signature, int sig_len);
void write_flash_header(FILE *file, device_type_t device);

#endif
