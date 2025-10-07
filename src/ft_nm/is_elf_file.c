#include "ft_nm.h"

/* For dprintf() */
#include "ft_printf.h"

/* For read() */
#include <unistd.h>


int is_elf_file( const char *filename, int fd, struct stat *st )
{
	unsigned char magic[4];

	/* Is File */
	if ( S_ISDIR( st->st_mode ) )
	{
		ft_dprintf( 2, "ft_nm: Warning : « %s » is a directory\n", filename );
		return ( 0 );
	}

	/* Is ELF File */
	if ( read( fd, magic, 4 ) != 4 ) //! Maybe add a -1 check
		return ( 0 );

	if ( magic[0] != 0x7f || magic[1] != 'E' || magic[2] != 'L' || magic[3] != 'F' )
		return ( 0 );

	return ( 1 );
}
