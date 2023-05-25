# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# includes
INCS = -Iupgrade -Icrypto -Icrypto/libtom

# flags
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O2 -g $(INCS)

# C compiler
CC = cc

# crypto
CRYPTO = crypto/md5.c crypto/ticrypto.c

# libtom
LIBTOM =\
	crypto/libtom/bncore.c\
	crypto/libtom/bn_error.c\
	crypto/libtom/bn_fast_mp_invmod.c\
	crypto/libtom/bn_fast_mp_montgomery_reduce.c\
	crypto/libtom/bn_fast_s_mp_mul_digs.c\
	crypto/libtom/bn_fast_s_mp_mul_high_digs.c\
	crypto/libtom/bn_fast_s_mp_sqr.c\
	crypto/libtom/bn_mp_2expt.c\
	crypto/libtom/bn_mp_abs.c\
	crypto/libtom/bn_mp_add.c\
	crypto/libtom/bn_mp_add_d.c\
	crypto/libtom/bn_mp_addmod.c\
	crypto/libtom/bn_mp_and.c\
	crypto/libtom/bn_mp_clamp.c\
	crypto/libtom/bn_mp_clear.c\
	crypto/libtom/bn_mp_clear_multi.c\
	crypto/libtom/bn_mp_cmp.c\
	crypto/libtom/bn_mp_cmp_d.c\
	crypto/libtom/bn_mp_cmp_mag.c\
	crypto/libtom/bn_mp_cnt_lsb.c\
	crypto/libtom/bn_mp_copy.c\
	crypto/libtom/bn_mp_count_bits.c\
	crypto/libtom/bn_mp_div_2.c\
	crypto/libtom/bn_mp_div_2d.c\
	crypto/libtom/bn_mp_div_3.c\
	crypto/libtom/bn_mp_div.c\
	crypto/libtom/bn_mp_div_d.c\
	crypto/libtom/bn_mp_dr_is_modulus.c\
	crypto/libtom/bn_mp_dr_reduce.c\
	crypto/libtom/bn_mp_dr_setup.c\
	crypto/libtom/bn_mp_exch.c\
	crypto/libtom/bn_mp_expt_d.c\
	crypto/libtom/bn_mp_exptmod.c\
	crypto/libtom/bn_mp_exptmod_fast.c\
	crypto/libtom/bn_mp_exteuclid.c\
	crypto/libtom/bn_mp_fread.c\
	crypto/libtom/bn_mp_fwrite.c\
	crypto/libtom/bn_mp_gcd.c\
	crypto/libtom/bn_mp_get_int.c\
	crypto/libtom/bn_mp_grow.c\
	crypto/libtom/bn_mp_init.c\
	crypto/libtom/bn_mp_init_copy.c\
	crypto/libtom/bn_mp_init_multi.c\
	crypto/libtom/bn_mp_init_set.c\
	crypto/libtom/bn_mp_init_set_int.c\
	crypto/libtom/bn_mp_init_size.c\
	crypto/libtom/bn_mp_invmod.c\
	crypto/libtom/bn_mp_invmod_slow.c\
	crypto/libtom/bn_mp_is_square.c\
	crypto/libtom/bn_mp_jacobi.c\
	crypto/libtom/bn_mp_karatsuba_mul.c\
	crypto/libtom/bn_mp_karatsuba_sqr.c\
	crypto/libtom/bn_mp_lcm.c\
	crypto/libtom/bn_mp_lshd.c\
	crypto/libtom/bn_mp_mod_2d.c\
	crypto/libtom/bn_mp_mod.c\
	crypto/libtom/bn_mp_mod_d.c\
	crypto/libtom/bn_mp_montgomery_calc_normalization.c\
	crypto/libtom/bn_mp_montgomery_reduce.c\
	crypto/libtom/bn_mp_montgomery_setup.c\
	crypto/libtom/bn_mp_mul_2.c\
	crypto/libtom/bn_mp_mul_2d.c\
	crypto/libtom/bn_mp_mul.c\
	crypto/libtom/bn_mp_mul_d.c\
	crypto/libtom/bn_mp_mulmod.c\
	crypto/libtom/bn_mp_neg.c\
	crypto/libtom/bn_mp_n_root.c\
	crypto/libtom/bn_mp_or.c\
	crypto/libtom/bn_mp_prime_fermat.c\
	crypto/libtom/bn_mp_prime_is_divisible.c\
	crypto/libtom/bn_mp_prime_is_prime.c\
	crypto/libtom/bn_mp_prime_miller_rabin.c\
	crypto/libtom/bn_mp_prime_next_prime.c\
	crypto/libtom/bn_mp_prime_rabin_miller_trials.c\
	crypto/libtom/bn_mp_prime_random_ex.c\
	crypto/libtom/bn_mp_radix_size.c\
	crypto/libtom/bn_mp_radix_smap.c\
	crypto/libtom/bn_mp_rand.c\
	crypto/libtom/bn_mp_read_radix.c\
	crypto/libtom/bn_mp_read_signed_bin.c\
	crypto/libtom/bn_mp_read_unsigned_bin.c\
	crypto/libtom/bn_mp_reduce_2k.c\
	crypto/libtom/bn_mp_reduce_2k_l.c\
	crypto/libtom/bn_mp_reduce_2k_setup.c\
	crypto/libtom/bn_mp_reduce_2k_setup_l.c\
	crypto/libtom/bn_mp_reduce.c\
	crypto/libtom/bn_mp_reduce_is_2k.c\
	crypto/libtom/bn_mp_reduce_is_2k_l.c\
	crypto/libtom/bn_mp_reduce_setup.c\
	crypto/libtom/bn_mp_rshd.c\
	crypto/libtom/bn_mp_set.c\
	crypto/libtom/bn_mp_set_int.c\
	crypto/libtom/bn_mp_shrink.c\
	crypto/libtom/bn_mp_signed_bin_size.c\
	crypto/libtom/bn_mp_sqr.c\
	crypto/libtom/bn_mp_sqrmod.c\
	crypto/libtom/bn_mp_sqrt.c\
	crypto/libtom/bn_mp_sub.c\
	crypto/libtom/bn_mp_sub_d.c\
	crypto/libtom/bn_mp_submod.c\
	crypto/libtom/bn_mp_toom_mul.c\
	crypto/libtom/bn_mp_toom_sqr.c\
	crypto/libtom/bn_mp_toradix.c\
	crypto/libtom/bn_mp_toradix_n.c\
	crypto/libtom/bn_mp_to_signed_bin.c\
	crypto/libtom/bn_mp_to_signed_bin_n.c\
	crypto/libtom/bn_mp_to_unsigned_bin.c\
	crypto/libtom/bn_mp_to_unsigned_bin_n.c\
	crypto/libtom/bn_mp_unsigned_bin_size.c\
	crypto/libtom/bn_mp_xor.c\
	crypto/libtom/bn_mp_zero.c\
	crypto/libtom/bn_prime_tab.c\
	crypto/libtom/bn_reverse.c\
	crypto/libtom/bn_s_mp_add.c\
	crypto/libtom/bn_s_mp_exptmod.c\
	crypto/libtom/bn_s_mp_mul_digs.c\
	crypto/libtom/bn_s_mp_mul_high_digs.c\
	crypto/libtom/bn_s_mp_sqr.c\
	crypto/libtom/bn_s_mp_sub.c\

# upgrade
UPGRADE=\
	upgrade/devices.c\
	upgrade/intelhex.c\
	upgrade/upgrade.c\
