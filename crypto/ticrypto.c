#include <gmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <bsd/md5.h>
#include "ticrypto.h"

void initialize_key(tikey_t *key) {
	mpz_init(key->n);
	mpz_init(key->p);
	mpz_init(key->q);
	mpz_init(key->D);
}

uint8_t *sign_os(uint8_t *header, int headerlen, uint8_t *data, int datalen, tikey_t key) {
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, header, headerlen);
	MD5Update(&md5, data, datalen);
	MD5Pad(&md5);
	uint8_t *digest = malloc(MD5_DIGEST_LENGTH);
	MD5Final(digest, &md5);
	return NULL;
}

void reverse_endianness(char *str) {
	int len = strlen(str);
	int i, j;
	char u, l;
	for (i = 0, j = len - 2; i < j; i += 2, j -= 2) {
		u = str[i];
		l = str[i + 1];
		str[i] = str[j];
		str[i + 1] = str[j + 1];
		str[j] = u;
		str[j + 1] = l;
	}
}

void parse_key(tikey_t *key, char *str) {
	int i;
	int l = strlen(str);
	for (i = 0; i < l; i++) {
		if (str[i] == '\n') {
			str[i] = 0;
		}
	}
	str += 2;
	reverse_endianness(str);
	mpz_set_str(key->n, str, 16);

	str += strlen(str) + 3;
	reverse_endianness(str);
	mpz_set_str(key->p, str, 16);

	str += strlen(str) + 3;
	reverse_endianness(str);
	mpz_set_str(key->q, str, 16);
}

void gen_exponent(tikey_t *key) {
	mpz_t e, p, q;
	mpz_init_set_ui(e, 17);
	mpz_init_set(p, key->p);
	mpz_init_set(q, key->q);

	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_mul(p, p, q);
	mpz_invert(key->D, e, p);

	mpz_clear(e);
	mpz_clear(p);
	mpz_clear(q);
}
