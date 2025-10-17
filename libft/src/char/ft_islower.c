#include "char.h"

int  ft_islower( int c )
{
	if ( 'a' <= c && c <= 'z' )
		return ( 1 );
	return ( 0 );
}