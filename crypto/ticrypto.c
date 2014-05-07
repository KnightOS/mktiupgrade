#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include "md5.h"
#include "tommath.h"
#include "ticrypto.h"

void initialize_key(tikey_t *key) {
	mp_init(&key->n);
	mp_init(&key->p);
	mp_init(&key->q);
	mp_init(&key->D);
}

void reverse(unsigned char *data, int len) {
	int i, j;
	char u;
	for (i = 0, j = len - 1; i < j; i++, j--) {
		u = data[i];
		data[i] = data[j];
		data[j] = u;
	}
}

uint8_t *sign_os(uint8_t *header, int headerlen, uint8_t *data, int datalen, tikey_t key, size_t *siglen) {
	MD5_CTX md5;
	MD5_Init(&md5);
	MD5_Update(&md5, header, headerlen);
	MD5_Update(&md5, data, datalen);
	uint8_t *digest = malloc(16);
	MD5_Final(digest, &md5);
	reverse(digest, 16);

	mp_int hash;
	mp_init(&hash);
	mp_read_unsigned_bin(&hash, digest, 16);

	mp_exptmod(&hash, &key.D, &key.n, &hash);

	int size = mp_unsigned_bin_size(&hash);
	uint8_t *signature = malloc(size + 3);
	mp_to_unsigned_bin(&hash, signature + 3);
	reverse(signature + 3, size);
	signature[0] = 0x02;
	signature[1] = 0x0D;
	signature[2] = 0x40;
	*siglen = size + 3;

	return signature;
}

void reverse_endianness(char *str) {
	int len = strlen(str);
	int i, j;
	char u, l;
	if (len % 2 == 1) {
		len--;
	}
	for (i = 0, j = len - 2; i < j; i += 2, j -= 2) {
		u = str[i];
		l = str[i + 1];
		str[i] = str[j];
		str[i + 1] = str[j + 1];
		str[j] = u;
		str[j + 1] = l;
	}
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
	mp_read_radix(&key->n, str, 16);

	str += strlen(str) + 3;
	reverse_endianness(str);
	mp_read_radix(&key->p, str, 16);

	str += strlen(str) + 3;
	reverse_endianness(str);
	mp_read_radix(&key->q, str, 16);
}

void gen_exponent(tikey_t *key) {
	mp_int e, p, q;
	mp_init_set_int(&e, 17);
	mp_init_copy(&p, &key->p);
	mp_init_copy(&q, &key->q);

	mp_sub_d(&p, 1, &p);
	mp_sub_d(&q, 1, &q);
	mp_mul(&q, &p, &p);
	mp_invmod(&e, &p, &key->D);

	mp_clear(&e);
	mp_clear(&p);
	mp_clear(&q);
}
