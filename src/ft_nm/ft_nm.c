#include "ft_nm.h"

/* For ft_dprintf() */
#include "ft_printf.h"

/* For open() */
#include <fcntl.h>

/* For close() */
#include <unistd.h>

/* For perror() */
#include <stdio.h>

/* For errno */
#include <errno.h>

/* For mmap(), munmap() */
#include <sys/mman.h>


static int ft_nm( const char *filename )
{
	int         fd;
	struct stat st;
	void        *map;

	/* Open File */
	fd = open( filename, O_RDONLY );
	if ( fd == -1 )
	{
		if ( errno == ENOENT )
			ft_dprintf( 2, "ft_nm: « %s »: no such file\n", filename ); //! faire gaffe pcq c est pas le bon fichier
		else
		{
			ft_dprintf( 2, "ft_nm: %s: ", filename );
			perror( NULL );
		}
		return ( 0 );
	}

	/* Initialize stat */
	if ( fstat( fd, &st ) < 0 )
	{
		perror( "fstat()" );
		close( fd );
		return ( 0 );
	}

	/* Is File */
	if ( S_ISDIR( st.st_mode ) )
	{
		ft_dprintf( 2, "ft_nm: Warning : « %s » is a directory\n", filename );
		return ( 0 );
	}

	/* Map File */
	map = mmap( NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0 );
	if ( map == MAP_FAILED )
	{
		perror( "mmap()" );
		close( fd );
		return ( 0 );
	}

	process_file( filename, fd, &st, map );

	close( fd );

	return ( 1 );
}


int ft_nm_wrapper( t_opts *opts )
{
	int    error_code = 0;
	char   *filename;
	t_list *node;

	node = opts->files;

	for ( int i = 0; i < opts->nb_files; i += 1 )
	{
		filename = node->content;
		node = node->next;

		if ( !ft_nm( filename ) )
		{
			error_code = 1;
			continue;
		}
	}

	return ( error_code );
}
