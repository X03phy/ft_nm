#include "ft_nm.h"
#include "fd.h"

#include <stdio.h>

void ft_nm_error( const char *filename )
{
	ft_putstr_fd( "ft_nm: ", 2 );
	perror( filename );
}

void ft_nm_file_error( const char *filename, const char *message )
{
	ft_putstr_fd( "ft_nm: Warning « ", 2 );
	ft_putstr_fd( filename, 2 );
	ft_putstr_fd( " »: ", 2 );
	ft_putendl_fd( message, 2 );
}
