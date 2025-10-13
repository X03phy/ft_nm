#include "ft_nm.h"

/* For ft_dprintf() */
#include "ft_printf.h"

#include <elf.h>

/* Code */
int process_file( const char *filename, int fd, struct stat *st, void *map )
{
	(void) st;
	(void) fd;
	unsigned char *e_ident = (unsigned char *) map;

	if ( e_ident[0] != 0x7F || e_ident[1] != 'E' || e_ident[2] != 'L' ||
		  e_ident[3] != 'F' )
		return ( 0 );

	if ( e_ident[EI_CLASS] == ELFCLASS64 )
		return ( process_elf64( map ) );
	// else if ( e_ident[EI_CLASS] == ELFCLASS32 )
	// 	return ( process_elf32(  ) );
	else
	{
		ft_dprintf( 2, "ft_nm: « %s » invalid ELF class\n", filename );
		return ( 0 );
	}

	return ( 1 );
}
