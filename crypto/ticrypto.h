#include "tommath.h"

#ifndef TICRYPTO_H
#define TICRYPTO_H

typedef struct {
	mp_int n, p, q, D;
} tikey_t;

void initialize_key(tikey_t *key);
void parse_key(tikey_t *key, char *str);
void gen_exponent(tikey_t *key);
uint8_t *sign_os(uint8_t *header, int headerlen, uint8_t *data, int datalen, tikey_t key, size_t *siglen);

#endif
