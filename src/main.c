#include "ft_nm.h"

int main( int argc, char **argv )
{
	t_opts opts;
	int    error_code;

	parse_input( &opts, argc, argv );

	error_code = ft_nm_wrapper( &opts );

	return ( error_code );
}
