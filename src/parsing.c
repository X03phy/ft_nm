#include "ft_nm.h"
#include "memory.h"

/* For exit() */
#include <stdlib.h>

void parse_input( t_opts *opts, int argc, char **argv )
{
	t_list *new;

	ft_bzero( opts, sizeof(t_opts) );

	for ( int i = 1; i < argc; i += 1 )
	{
		new = ft_lstnew( argv[i] );
		if ( !new )
		{
			// free struct
			exit( 1 );
		}
		ft_lstadd_back( &( opts->files ), new );
		opts->nb_files += 1;
	}

	if ( opts->files == NULL )
	{
		new = ft_lstnew( "a.out" );
		if ( !new )
		{
			// free struct
			exit( 1 );
		}
		ft_lstadd_back( &( opts->files ), new );
		opts->nb_files += 1;
	}
}
