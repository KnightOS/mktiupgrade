#ifndef UPGRADE_H
#define UPGRADE_H

uint8_t *create_header(uint8_t key_name, uint8_t major_version, uint8_t minor_version, uint8_t hardware_revision, uint8_t pages, int *length);

#endif
