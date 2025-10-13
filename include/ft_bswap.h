#ifndef FT_BSWAP_H
#define FT_BSWAP_H

/* Headers */
/* For uintX_t */
#include <stdint.h>

/* Prototypes */
static inline uint16_t ft_bswap16( uint16_t x )
{
	return ( ( ( x >> 8 ) & 0x00FFU ) | ( ( x << 8 ) & 0xFF00U ) );
}

static inline uint32_t ft_bswap32( uint32_t x )
{
	return ( ( x >> 24 ) & 0x000000FFUL ) | ( ( x << 24 ) & 0xFF000000UL ) |
			 ( ( x >> 8 ) & 0x0000FF00UL ) | ( ( x << 8 ) & 0x00FF0000UL );
}

static inline uint64_t ft_bswap64( uint64_t x )
{
	return ( ( x >> 56 ) & 0x00000000000000FFULL ) |
			 ( ( x >> 40 ) & 0x000000000000FF00ULL ) |
			 ( ( x >> 24 ) & 0x0000000000FF0000ULL ) |
			 ( ( x >> 8 ) & 0x00000000FF000000ULL ) |
			 ( ( x << 8 ) & 0x000000FF00000000ULL ) |
			 ( ( x << 24 ) & 0x0000FF0000000000ULL ) |
			 ( ( x << 40 ) & 0x00FF000000000000ULL ) |
			 ( ( x << 56 ) & 0xFF00000000000000ULL );
}

#endif
