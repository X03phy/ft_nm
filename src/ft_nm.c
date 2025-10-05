#include "ft_nm.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

static int is_elf_file( const char *filename )
{
	int           fd;
	struct stat	  st;
	unsigned char magic[4];

	fd = open( filename, O_RDONLY );
	if ( fd == -1 )
	{
		if ( errno == ENOENT )
			ft_nm_file_error( filename, "no such file" ); //! faire gaffe pcq c est pas le bon fichier
		else
			ft_nm_error( filename );
		return ( 0 );
	}

	/* Is File */
	if ( fstat( fd, &st ) < 0 )
	{
		perror( "fstat()" );
		close( fd );
		return ( 0 );
	}

	if ( S_ISDIR( st.st_mode ) )
	{
		ft_nm_file_error( filename, "is a directory" );
		close( fd );
		return ( 0 );
	}

	if ( !S_ISREG( st.st_mode ) )
	{
		ft_nm_file_error( filename, "no such file" );
		close( fd );
		return ( 0 );
	}

	/* Is ELF File */
	if ( read( fd, magic, 4 ) != 4 ) //! Maybe add a -1 check
	{
		close( fd );
		return ( 0 );
	}

	close( fd );

	if ( magic[0] != 0x7f || magic[1] != 'E' || magic[2] != 'L' || magic[3] != 'F' )
		return ( 0 );

	return ( 1 );
}

// static int process_elf( const char *filename )
// {

// }

int ft_nm( t_opts *opts )
{
	int    error_code = 0;
	char   *filename;
	t_list *node;

	node = opts->files;

	for ( int i = 0; i < opts->nb_files; i += 1 )
	{
		filename = node->content;
		node = node->next;

		if ( !is_elf_file( filename ) )
		{
			error_code = 1;
			continue;
		}
	}

	return ( error_code );
}
