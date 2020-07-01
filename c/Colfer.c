// Code generated by colf(1); DO NOT EDIT.
// The compiler used schema file test.colf for package gen.

#include "Colfer.h"
#include <errno.h>
#include <stdlib.h>
#include <time.h>


#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB__) || \
    defined(__SYSC_ZARCH__)
#define COLFER_ENDIAN
#endif


size_t colfer_size_max = 16 * 1024 * 1024;
size_t colfer_list_max = 64 * 1024;



size_t gen_o_marshal_len(const gen_o* o) {
	size_t l = 1;

	if (o->b) l++;

	{
		uint_fast32_t x = o->u32;
		if (x) {
			if (x >= (uint_fast32_t) 1 << 21) l += 5;
			else for (l += 2; x > 127; x >>= 7, ++l);
		}
	}

	{
		uint_fast64_t x = o->u64;
		if (x) {
			if (x >= (uint_fast64_t) 1 << 49) l += 9;
			else for (l += 2; x > 127; x >>= 7, ++l);
		}
	}

	{
		uint_fast32_t x = o->i32;
		if (x) {
			if (x & (uint_fast32_t) 1 << 31) {
				x = ~x;
				++x;
			}
			for (l += 2; x > 127; x >>= 7, ++l);
		}
	}

	{
		uint_fast64_t x = o->i64;
		if (x) {
			if (x & (uint_fast64_t) 1 << 63) {
				x = ~x;
				++x;
			}
			size_t max = l + 10;
			for (l += 2; x > 127 && l < max; x >>= 7, ++l);
		}
	}

	if (o->f32 != 0.0f) l += 5;

	if (o->f64 != 0.0) l += 9;

	{
		time_t s = o->t.tv_sec;
		long ns = o->t.tv_nsec;
		if (s || ns) {
			s += ns / 1000000000;
			l += s >= (time_t) 1 << 32 || s < 0 ? 13 : 9;
		}
	}

	{
		size_t n = o->s.len;
		if (n > colfer_size_max) {
			errno = EFBIG;
			return 0;
		}
		if (n) for (l += 2 + n; n > 127; n >>= 7, ++l);
	}

	{
		size_t n = o->a.len;
		if (n > colfer_size_max) {
			errno = EFBIG;
			return 0;
		}
		if (n) for (l += 2 + n; n > 127; n >>= 7, ++l);
	}

	{
		if (o->o) l += 1 + gen_o_marshal_len(o->o);
	}

	{
		size_t n = o->os.len;
		if (n) {
			if (n > colfer_list_max) {
				errno = EFBIG;
				return 0;
			}
			gen_o* a = o->os.list;
			for (size_t i = 0; i < n; ++i) l += gen_o_marshal_len(&a[i]);
			for (l += 2; n > 127; n >>= 7, ++l);
			if (l > colfer_size_max) {
				errno = EFBIG;
				return 0;
			}
		}
	}

	{
		size_t n = o->ss.len;
		if (n) {
			if (n > colfer_list_max) {
				errno = EFBIG;
				return 0;
			}
			colfer_text* a = o->ss.list;
			for (size_t i = 0; i < n; ++i) {
				size_t len = a[i].len;
				if (len > colfer_size_max) {
					errno = EFBIG;
					return 0;
				}
				for (l += len + 1; len > 127; len >>= 7, ++l);
			}
			for (l += 2; n > 127; n >>= 7, ++l);
			if (l > colfer_size_max) {
				errno = EFBIG;
				return 0;
			}
		}
	}

	{
		size_t n = o->as.len;
		if (n) {
			if (n > colfer_list_max) {
				errno = EFBIG;
				return 0;
			}
			colfer_binary* a = o->as.list;
			for (size_t i = 0; i < n; ++i) {
				size_t len = a[i].len;
				if (len > colfer_size_max) {
					errno = EFBIG;
					return 0;
				}
				for (l += len + 1; len > 127; len >>= 7, ++l);
			}
			for (l += 2; n > 127; n >>= 7, ++l);
			if (l > colfer_size_max) {
				errno = EFBIG;
				return 0;
			}
		}
	}

	if (o->u8) l += 2;

	{
		uint_fast16_t x = o->u16;
		if (x) l += x < 256 ? 2 : 3;
	}

	{
		size_t n = o->f32s.len;
		if (n) {
			if (n > colfer_list_max) {
				errno = EFBIG;
				return 0;
			}
			for (l += n * 4 + 2; n > 127; n >>= 7, ++l);
		}
	}

	{
		size_t n = o->f64s.len;
		if (n) {
			if (n > colfer_list_max) {
				errno = EFBIG;
				return 0;
			}
			for (l += n * 8 + 2; n > 127; n >>= 7, ++l);
		}
	}

	if (l > colfer_size_max) {
		errno = EFBIG;
		return 0;
	}
	return l;
}

size_t gen_o_marshal(const gen_o* o, void* buf) {
	// octet pointer navigation
	uint8_t* p = buf;

	if (o->b) *p++ = 0;

	{
		uint_fast32_t x = o->u32;
		if (x) {
			if (x < (uint_fast32_t) 1 << 21) {
				*p++ = 1;
				for (; x >= 128; x >>= 7) *p++ = x | 128;
				*p++ = x;
			} else {
				*p++ = 1 | 128;
#ifdef COLFER_ENDIAN
				memcpy(p, &o->u32, 4);
				p += 4;
#else
				*p++ = x >> 24;
				*p++ = x >> 16;
				*p++ = x >> 8;
				*p++ = x;
#endif
			}
		}
	}

	{
		uint_fast64_t x = o->u64;
		if (x) {
			if (x < (uint_fast64_t) 1 << 49) {
				*p++ = 2;
				for (; x >= 128; x >>= 7) *p++ = x | 128;
				*p++ = x;
			} else {
				*p++ = 2 | 128;
#ifdef COLFER_ENDIAN
				memcpy(p, &o->u64, 8);
				p += 8;
#else
				*p++ = x >> 56;
				*p++ = x >> 48;
				*p++ = x >> 40;
				*p++ = x >> 32;
				*p++ = x >> 24;
				*p++ = x >> 16;
				*p++ = x >> 8;
				*p++ = x;
#endif
			}
		}
	}

	{
		uint_fast32_t x = o->i32;
		if (x) {
			if (x & (uint_fast32_t) 1 << 31) {
				*p++ = 3 | 128;
				x = ~x + 1;
			} else	*p++ = 3;

			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;
		}
	}

	{
		uint_fast64_t x = o->i64;
		if (x) {
			if (x & (uint_fast64_t) 1 << 63) {
				*p++ = 4 | 128;
				x = ~x + 1;
			} else	*p++ = 4;

			uint8_t* max = p + 8;
			for (; x >= 128 && p < max; x >>= 7) *p++ = x | 128;
			*p++ = x;
		}
	}

	if (o->f32 != 0.0f) {
		*p++ = 5;

#ifdef COLFER_ENDIAN
		memcpy(p, &o->f32, 4);
		p += 4;
#else
		uint_fast32_t x;
		memcpy(&x, &o->f32, 4);
		*p++ = x >> 24;
		*p++ = x >> 16;
		*p++ = x >> 8;
		*p++ = x;
#endif
	}

	if (o->f64 != 0.0) {
		*p++ = 6;

#ifdef COLFER_ENDIAN
		memcpy(p, &o->f64, 8);
		p += 8;
#else
		uint_fast64_t x;
		memcpy(&x, &o->f64, 8);
		*p++ = x >> 56;
		*p++ = x >> 48;
		*p++ = x >> 40;
		*p++ = x >> 32;
		*p++ = x >> 24;
		*p++ = x >> 16;
		*p++ = x >> 8;
		*p++ = x;
#endif
	}

	{
		time_t s = o->t.tv_sec;
		long ns = o->t.tv_nsec;
		if (s || ns) {
			static const int_fast64_t nano = 1000000000;
			s += ns / nano;
			ns %= nano;
			if (ns < 0) {
				--s;
				ns += nano;
			}

			uint_fast64_t x = s;
			if (x < (uint_fast64_t) 1 << 32)
				*p++ = 7;
			else {
				*p++ = 7 | 128;

				*p++ = x >> 56;
				*p++ = x >> 48;
				*p++ = x >> 40;
				*p++ = x >> 32;
			}
			*p++ = x >> 24;
			*p++ = x >> 16;
			*p++ = x >> 8;
			*p++ = x;

			x = ns;
			*p++ = x >> 24;
			*p++ = x >> 16;
			*p++ = x >> 8;
			*p++ = x;
		}
	}

	{
		size_t n = o->s.len;
		if (n) {
			*p++ = 8;

			uint_fast32_t x = n;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

			memcpy(p, o->s.utf8, n);
			p += n;
		}
	}

	{
		size_t n = o->a.len;
		if (n) {
			*p++ = 9;

			uint_fast32_t x = n;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

			memcpy(p, o->a.octets, n);
			p += n;
		}
	}

	{
		if (o->o) {
			*p++ = 10;

			p += gen_o_marshal(o->o, p);
		}
	}

	{
		size_t n = o->os.len;
		if (n) {
			*p++ = 11;

			uint_fast32_t x = n;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

			gen_o* a = o->os.list;
			for (size_t i = 0; i < n; ++i) p += gen_o_marshal(&a[i], p);
		}
	}

	{
		size_t count = o->ss.len;
		if (count) {
			*p++ = 12;

			uint_fast32_t x = count;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

			colfer_text* text = o->ss.list;
			do {
				size_t n = text->len;
				for (x = n; x >= 128; x >>= 7) *p++ = x | 128;
				*p++ = x;

				memcpy(p, text->utf8, n);
				p += n;

				++text;
			} while (--count != 0);
		}
	}

	{
		size_t count = o->as.len;
		if (count) {
			*p++ = 13;

			uint_fast32_t x = count;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

			colfer_binary* binary = o->as.list;
			do {
				size_t n = binary->len;
				for (x = n; x >= 128; x >>= 7) *p++ = x | 128;
				*p++ = x;

				memcpy(p, binary->octets, n);
				p += n;

				++binary;
			} while (--count != 0);
		}
	}

	if (o->u8) {
		*p++ = 14;

		*p++ = o->u8;
	}

	{
		uint_fast16_t x = o->u16;
		if (x) {
			if (x < 256)  {
				*p++ = 15 | 0x80;

				*p++ = x;
			} else {
				*p++ = 15;

				*p++ = x >> 8;
				*p++ = x;
			}
		}
	}

	{
		size_t n = o->f32s.len;
		if (n) {
			*p++ = 16;

			uint_fast32_t x = n;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

#ifdef COLFER_ENDIAN
			memcpy(p, o->f32s.list, n * 4);
			p += n * 4;
#else
			uint32_t* fp = (uint32_t*) o->f32s.list;
			for (;;) {
				memcpy(&x, fp, 4);
				*p++ = x >> 24;
				*p++ = x >> 16;
				*p++ = x >> 8;
				*p++ = x;
				if (--n == 0) break;
				++fp;
			}
#endif
		}
	}

	{
		size_t n = o->f64s.len;
		if (n) {
			*p++ = 17;

			uint_fast32_t x = n;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

#ifdef COLFER_ENDIAN
			memcpy(p, o->f64s.list, n * 8);
			p += n * 8;
#else
			uint64_t* fp = (uint64_t*) o->f64s.list;
			for (;;) {
				uint_fast64_t x;
				memcpy(&x, fp, 8);
				*p++ = x >> 56;
				*p++ = x >> 48;
				*p++ = x >> 40;
				*p++ = x >> 32;
				*p++ = x >> 24;
				*p++ = x >> 16;
				*p++ = x >> 8;
				*p++ = x;
				if (--n == 0) break;
				++fp;
			}
#endif
		}
	}

	*p++ = 127;

	return p - (uint8_t*) buf;
}

size_t gen_o_unmarshal(gen_o* o, const void* data, size_t datalen) {
	// octet pointer navigation
	const uint8_t* p = data;
	const uint8_t* end;
	int enderr;
	if (datalen < colfer_size_max) {
		end = p + datalen;
		enderr = EWOULDBLOCK;
	} else {
		end = p + colfer_size_max;
		enderr = EFBIG;
	}

	if (p >= end) {
		errno = enderr;
		return 0;
	}
	uint_fast8_t header = *p++;

	if (header == 0) {
		o->b = 1;
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		header = *p++;
	}

	if (header == 1) {
		if (p+1 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast32_t x = *p++;
		if (x > 127) {
			x &= 127;
			for (int shift = 7; ; shift += 7) {
				uint_fast32_t b = *p++;
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				if (b <= 127) {
					x |= b << shift;
					break;
				}
				x |= (b & 127) << shift;
			}
		}
		o->u32 = x;
		header = *p++;
	} else if (header == (1 | 128)) {
		if (p+4 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast32_t x = *p++;
		x <<= 24;
		x |= (uint_fast32_t) *p++ << 16;
		x |= (uint_fast32_t) *p++ << 8;
		x |= (uint_fast32_t) *p++;
		o->u32 = x;
		header = *p++;
	}

	if (header == 2) {
		if (p+1 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast64_t x = *p++;
		if (x > 127) {
			x &= 127;
			for (int shift = 7; ; shift += 7) {
				uint_fast64_t b = *p++;
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				if (b <= 127) {
					x |= b << shift;
					break;
				}
				x |= (b & 127) << shift;
			}
		}
		o->u64 = x;
		header = *p++;
	} else if (header == (2 | 128)) {
		if (p+8 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast64_t x = *p++;
		x <<= 56;
		x |= (uint_fast64_t) *p++ << 48;
		x |= (uint_fast64_t) *p++ << 40;
		x |= (uint_fast64_t) *p++ << 32;
		x |= (uint_fast64_t) *p++ << 24;
		x |= (uint_fast64_t) *p++ << 16;
		x |= (uint_fast64_t) *p++ << 8;
		x |= (uint_fast64_t) *p++;
		o->u64 = x;
		header = *p++;
	}

	if ((header & 127) == 3) {
		if (p+1 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast32_t x = *p++;
		if (x > 127) {
			x &= 127;
			for (int shift = 7; shift < 35; shift += 7) {
				uint_fast32_t b = *p++;
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				if (b <= 127) {
					x |= b << shift;
					break;
				}
				x |= (b & 127) << shift;
			}
		}
		if (header & 128) x = ~x + 1;
		o->i32 = x;
		header = *p++;
	}

	if ((header & 127) == 4) {
		if (p+1 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast64_t x = *p++;
		if (x > 127) {
			x &= 127;
			for (int shift = 7; ; shift += 7) {
				uint_fast64_t b = *p++;
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				if (b <= 127 || shift == 56) {
					x |= b << shift;
					break;
				}
				x |= (b & 127) << shift;
			}
		}
		if (header & 128) x = ~x + 1;
		o->i64 = x;
		header = *p++;
	}

	if (header == 5) {
		if (p+4 >= end) {
			errno = enderr;
			return 0;
		}
#ifdef COLFER_ENDIAN
		memcpy(&o->f32, p, 4);
		p += 4;
#else
		uint_fast32_t x = *p++;
		x <<= 24;
		x |= (uint_fast32_t) *p++ << 16;
		x |= (uint_fast32_t) *p++ << 8;
		x |= (uint_fast32_t) *p++;
		memcpy(&o->f32, &x, 4);
#endif
		header = *p++;
	}

	if (header == 6) {
		if (p+8 >= end) {
			errno = enderr;
			return 0;
		}
#ifdef COLFER_ENDIAN
		memcpy(&o->f64, p, 8);
		p += 8;
#else
		uint_fast64_t x = *p++;
		x <<= 56;
		x |= (uint_fast64_t) *p++ << 48;
		x |= (uint_fast64_t) *p++ << 40;
		x |= (uint_fast64_t) *p++ << 32;
		x |= (uint_fast64_t) *p++ << 24;
		x |= (uint_fast64_t) *p++ << 16;
		x |= (uint_fast64_t) *p++ << 8;
		x |= (uint_fast64_t) *p++;
		memcpy(&o->f64, &x, 8);
#endif
		header = *p++;
	}

	if ((header & 127) == 7) {
		if (header & 128) {
			if (p+12 >= end) {
				errno = enderr;
				return 0;
			}
			uint64_t x = *p++;
			x <<= 56;
			x |= (uint64_t) *p++ << 48;
			x |= (uint64_t) *p++ << 40;
			x |= (uint64_t) *p++ << 32;
			x |= (uint64_t) *p++ << 24;
			x |= (uint64_t) *p++ << 16;
			x |= (uint64_t) *p++ << 8;
			x |= (uint64_t) *p++;
			o->t.tv_sec = (time_t)(int64_t) x;
		} else {
			if (p+8 >= end) {
				errno = enderr;
				return 0;
			}
			uint_fast32_t x = *p++;
			x <<= 24;
			x |= (uint_fast32_t) *p++ << 16;
			x |= (uint_fast32_t) *p++ << 8;
			x |= (uint_fast32_t) *p++;
			o->t.tv_sec = (time_t) x;
		}
		uint_fast32_t x = *p++;
		x <<= 24;
		x |= (uint_fast32_t) *p++ << 16;
		x |= (uint_fast32_t) *p++ << 8;
		x |= (uint_fast32_t) *p++;
		o->t.tv_nsec = (long) x;
		header = *p++;
	}

	if (header == 8) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; shift < sizeof(size_t) * CHAR_BIT; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_size_max) {
			errno = EFBIG;
			return 0;
		}
		if (p+n >= end) {
			errno = enderr;
			return 0;
		}
		o->s.len = n;

		void* a = malloc(n);
		o->s.utf8 = (char*) a;
		if (n) {
			memcpy(a, p, n);
			p += n;
		}
		header = *p++;
	}

	if (header == 9) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; ; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_size_max) {
			errno = EFBIG;
			return 0;
		}
		if (p+n >= end) {
			errno = enderr;
			return 0;
		}
		o->a.len = n;

		void* a = malloc(n);
		o->a.octets = (uint8_t*) a;
		if (n) {
			memcpy(a, p, n);
			p += n;
		}
		header = *p++;
	}

	if (header == 10) {
		o->o = calloc(1, sizeof(gen_o));
		size_t read = gen_o_unmarshal(o->o, p, (size_t) (end - p));
		if (!read) {
			if (errno == EWOULDBLOCK) errno = enderr;
			return read;
		}
		p += read;

		if (p >= end) {
			errno = enderr;
			return 0;
		}
		header = *p++;
	}

	if (header == 11) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; ; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_list_max) {
			errno = EFBIG;
			return 0;
		}

		gen_o* a = calloc(n, sizeof(gen_o));
		for (size_t i = 0; i < n; ++i) {
			size_t read = gen_o_unmarshal(&a[i], p, (size_t) (end - p));
			if (!read) {
				if (errno == EWOULDBLOCK) errno = enderr;
				return read;
			}
			p += read;
		}
		o->os.len = n;
		o->os.list = a;

		if (p >= end) {
			errno = enderr;
			return 0;
		}
		header = *p++;
	}

	if (header == 12) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; ; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_list_max) {
			errno = EFBIG;
			return 0;
		}
		o->ss.len = n;

		colfer_text* text = malloc(n * sizeof(colfer_text));
		o->ss.list = text;
		for (; n; --n, ++text) {
			if (p >= end) {
				errno = enderr;
				return 0;
			}
			size_t len = *p++;
			if (len > 127) {
				len &= 127;
				for (int shift = 7; ; shift += 7) {
					if (p >= end) {
						errno = enderr;
						return 0;
					}
					size_t c = *p++;
					if (c <= 127) {
						len |= c << shift;
						break;
					}
					len |= (c & 127) << shift;
				}
			}
			if (len > colfer_size_max) {
				errno = EFBIG;
				return 0;
			}
			if (p+len >= end) {
				errno = enderr;
				return 0;
			}
			text->len = len;

			char* a = malloc(len);
			text->utf8 = a;
			if (len) {
				memcpy(a, p, len);
				p += len;
			}
		}

		if (p >= end) {
			errno = enderr;
			return 0;
		}
		header = *p++;
	}

	if (header == 13) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; ; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_list_max) {
			errno = EFBIG;
			return 0;
		}
		o->as.len = n;

		colfer_binary* binary = malloc(n * sizeof(colfer_binary));
		o->as.list = binary;
		for (; n; --n, ++binary) {
			if (p >= end) {
				errno = enderr;
				return 0;
			}
			size_t len = *p++;
			if (len > 127) {
				len &= 127;
				for (int shift = 7; ; shift += 7) {
					if (p >= end) {
						errno = enderr;
						return 0;
					}
					size_t c = *p++;
					if (c <= 127) {
						len |= c << shift;
						break;
					}
					len |= (c & 127) << shift;
				}
			}
			if (len > colfer_size_max) {
				errno = EFBIG;
				return 0;
			}
			if (p+len >= end) {
				errno = enderr;
				return 0;
			}
			binary->len = len;

			uint8_t* a = malloc(len);
			binary->octets = a;
			if (len) {
				memcpy(a, p, len);
				p += len;
			}
		}

		if (p >= end) {
			errno = enderr;
			return 0;
		}
		header = *p++;
	}

	if (header == 14) {
		if (p+1 >= end) {
			errno = enderr;
			return 0;
		}
		o->u8 = *p++;
		header = *p++;
	}

	if (header == 15) {
		if (p+2 >= end) {
			errno = enderr;
			return 0;
		}
		uint_fast16_t x = *p++;
		x <<= 8;
		o->u16 = x | *p++;
		header = *p++;
	} else if (header == (15 | 128)) {
		if (p+1 >= end) {
			errno = enderr;
			return 0;
		}
		o->u16 = *p++;
		header = *p++;
	}

	if (header == 16) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; ; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_list_max) {
			errno = EFBIG;
			return 0;
		}
		if (p+n*4 >= end) {
			errno = enderr;
			return 0;
		}
		o->f32s.len = n;

		float* fp = malloc(n * 4);
		o->f32s.list = fp;
#ifdef COLFER_ENDIAN
		memcpy(fp, p, n * 4);
		p += n * 4;
#else
		for (; n; --n, ++fp) {
			uint_fast32_t x = *p++;
			x <<= 24;
			x |= (uint_fast32_t) *p++ << 16;
			x |= (uint_fast32_t) *p++ << 8;
			x |= (uint_fast32_t) *p++;
			memcpy(fp, &x, 4);
		}
#endif
		header = *p++;
	}

	if (header == 17) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; ; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_list_max) {
			errno = EFBIG;
			return 0;
		}
		if (p+n*8 >= end) {
			errno = enderr;
			return 0;
		}
		o->f64s.len = n;

		double* fp = malloc(n * 8);
		o->f64s.list = fp;
#ifdef COLFER_ENDIAN
		memcpy(fp, p, n * 8);
		p += n * 8;
#else
		for (; n; --n, ++fp) {
			uint_fast64_t x = *p++;
			x <<= 56;
			x |= (uint_fast64_t) *p++ << 48;
			x |= (uint_fast64_t) *p++ << 40;
			x |= (uint_fast64_t) *p++ << 32;
			x |= (uint_fast64_t) *p++ << 24;
			x |= (uint_fast64_t) *p++ << 16;
			x |= (uint_fast64_t) *p++ << 8;
			x |= (uint_fast64_t) *p++;
			memcpy(fp, &x, 8);
		}
#endif
		header = *p++;
	}

	if (header != 127) {
		errno = EILSEQ;
		return 0;
	}

	return (size_t) (p - (const uint8_t*) data);
}

size_t gen_dromedary_case_marshal_len(const gen_dromedary_case* o) {
	size_t l = 1;

	{
		size_t n = o->pascal_case.len;
		if (n > colfer_size_max) {
			errno = EFBIG;
			return 0;
		}
		if (n) for (l += 2 + n; n > 127; n >>= 7, ++l);
	}

	if (l > colfer_size_max) {
		errno = EFBIG;
		return 0;
	}
	return l;
}

size_t gen_dromedary_case_marshal(const gen_dromedary_case* o, void* buf) {
	// octet pointer navigation
	uint8_t* p = buf;

	{
		size_t n = o->pascal_case.len;
		if (n) {
			*p++ = 0;

			uint_fast32_t x = n;
			for (; x >= 128; x >>= 7) *p++ = x | 128;
			*p++ = x;

			memcpy(p, o->pascal_case.utf8, n);
			p += n;
		}
	}

	*p++ = 127;

	return p - (uint8_t*) buf;
}

size_t gen_dromedary_case_unmarshal(gen_dromedary_case* o, const void* data, size_t datalen) {
	// octet pointer navigation
	const uint8_t* p = data;
	const uint8_t* end;
	int enderr;
	if (datalen < colfer_size_max) {
		end = p + datalen;
		enderr = EWOULDBLOCK;
	} else {
		end = p + colfer_size_max;
		enderr = EFBIG;
	}

	if (p >= end) {
		errno = enderr;
		return 0;
	}
	uint_fast8_t header = *p++;

	if (header == 0) {
		if (p >= end) {
			errno = enderr;
			return 0;
		}
		size_t n = *p++;
		if (n > 127) {
			n &= 127;
			for (int shift = 7; shift < sizeof(size_t) * CHAR_BIT; shift += 7) {
				if (p >= end) {
					errno = enderr;
					return 0;
				}
				size_t c = *p++;
				if (c <= 127) {
					n |= c << shift;
					break;
				}
				n |= (c & 127) << shift;
			}
		}
		if (n > colfer_size_max) {
			errno = EFBIG;
			return 0;
		}
		if (p+n >= end) {
			errno = enderr;
			return 0;
		}
		o->pascal_case.len = n;

		void* a = malloc(n);
		o->pascal_case.utf8 = (char*) a;
		if (n) {
			memcpy(a, p, n);
			p += n;
		}
		header = *p++;
	}

	if (header != 127) {
		errno = EILSEQ;
		return 0;
	}

	return (size_t) (p - (const uint8_t*) data);
}

size_t gen_embed_o_marshal_len(const gen_embed_o* o) {
	size_t l = 1;

	{
		if (o->inner) l += 1 + gen_o_marshal_len(o->inner);
	}

	if (l > colfer_size_max) {
		errno = EFBIG;
		return 0;
	}
	return l;
}

size_t gen_embed_o_marshal(const gen_embed_o* o, void* buf) {
	// octet pointer navigation
	uint8_t* p = buf;

	{
		if (o->inner) {
			*p++ = 0;

			p += gen_o_marshal(o->inner, p);
		}
	}

	*p++ = 127;

	return p - (uint8_t*) buf;
}

size_t gen_embed_o_unmarshal(gen_embed_o* o, const void* data, size_t datalen) {
	// octet pointer navigation
	const uint8_t* p = data;
	const uint8_t* end;
	int enderr;
	if (datalen < colfer_size_max) {
		end = p + datalen;
		enderr = EWOULDBLOCK;
	} else {
		end = p + colfer_size_max;
		enderr = EFBIG;
	}

	if (p >= end) {
		errno = enderr;
		return 0;
	}
	uint_fast8_t header = *p++;

	if (header == 0) {
		o->inner = calloc(1, sizeof(gen_o));
		size_t read = gen_o_unmarshal(o->inner, p, (size_t) (end - p));
		if (!read) {
			if (errno == EWOULDBLOCK) errno = enderr;
			return read;
		}
		p += read;

		if (p >= end) {
			errno = enderr;
			return 0;
		}
		header = *p++;
	}

	if (header != 127) {
		errno = EILSEQ;
		return 0;
	}

	return (size_t) (p - (const uint8_t*) data);
}