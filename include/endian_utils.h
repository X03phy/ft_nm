#ifndef ENDIAN_UTILS_H
#define ENDIAN_UTILS_H


/* Headers */
/* For uintX_t */
#include <stdint.h>


/* For ft_bwapX() */
#include "ft_bswap.h"


#include <endian.h>


/* Macros */
#define NEED_SWAP( file_is_little_endian ) ( file_is_little_endian != ( __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ) )


/* Prototypes */
static inline uint16_t read16( uint16_t x, int file_is_little_endian )
{
	if ( NEED_SWAP( file_is_little_endian ) )
		return ( ft_bswap16( x ) );
	return ( x );
}


static inline uint32_t read32( uint32_t x, int file_is_little_endian )
{
	if ( NEED_SWAP( file_is_little_endian ) )
		return ( ft_bswap16( x ) );
	return ( x );
}


static inline uint64_t read64( uint64_t x, int file_is_little_endian )
{
	if ( NEED_SWAP( file_is_little_endian ) )
		return ( ft_bswap16( x ) );
	return ( x );
}


#endif
