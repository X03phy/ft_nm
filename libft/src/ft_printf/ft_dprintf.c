#include "ft_printf.h"

/* For va_list, va_start(), va_arg(), va_end() */
#include <stdarg.h>

/* For write() */
#include <unistd.h>

/* For ft_strlen() */
#include "string.h"

static int ft_convert( const int fd, const char spec, va_list ap )
{
	if ( spec == 's' )
	{
		char *str = va_arg( ap, char * );
		return ( write( fd, str, ft_strlen( str ) ) );
	}

	else if ( spec == 'c' )
	{
		char c = va_arg( ap, int );
		return ( write( fd, &c, 1 ) );
	}

	else
		return ( write( fd, "%", 1 ) );
}

int ft_dprintf( int fd, const char *format, ... )
{
	int	  count = 0;
	va_list ap;

	if ( fd < 0 || 1023 < fd || format == NULL )
		return ( -1 );

	va_start( ap, format );
	for ( int i = 0; format[i]; i += 1 )
	{
		if ( format[i] == '%' )
		{
			i += 1;
			if ( !format[i] )
				break;
			count += ft_convert( fd, format[i], ap );
		}
		else
			count += write( fd, &format[i], 1 );
	}
	va_end( ap );

	return ( count );
}
