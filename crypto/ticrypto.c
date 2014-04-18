#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <openssl/md5.h>
#include "ticrypto.h"

void initialize_key(tikey_t *key) {
	mpz_init(key->n);
	mpz_init(key->p);
	mpz_init(key->q);
	mpz_init(key->D);
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
uint8_t *sign_os(uint8_t *header, int headerlen, uint8_t *data, int datalen, tikey_t key, size_t *siglen) {
	MD5_CTX md5;
	MD5_Init(&md5);
	MD5_Update(&md5, header, headerlen);
	MD5_Update(&md5, data, datalen);
	uint8_t *digest = malloc(MD5_DIGEST_LENGTH);
	MD5_Final(digest, &md5);

	char digeststr[34];
	int i, j;
	for (i = 0, j = 15; i < 16; i++, j--) {
		sprintf(&digeststr[i * 2], "%02x", (unsigned int)digest[j]);
	}
	digeststr[33] = 0;

	mpz_t hash;
	mpz_init_set_str(hash, digeststr, 16);

	mpz_powm(hash, hash, key.D, key.n);

	uint8_t *signature = NULL;
	mpz_export(signature, siglen, 1, 1, 1, 0, hash);
	signature = realloc(signature, *siglen + 1); /* Add space for encoding stuff */
	memmove(signature + 3, signature, *siglen - 2);
	signature[0] = 0x02;
	signature[1] = 0x0D;
	signature[2] = 0x40;
	*siglen += 1;

	return signature;
}


void parse_key(tikey_t *key, char *_str) {
	char *str = _str;
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
