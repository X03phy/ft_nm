#ifndef FT_NM_H
#define FT_NM_H

/* Headers */
/* For struct stat, fstat() */
#include <sys/stat.h>

/* For t_list */
#include "linked_list.h"

/* Structures */
typedef struct s_opts
{
	int	  flags;
	t_list *files;
	int	  nb_files;
} t_opts;

/* Prototypes */
/* Parsing */
int parse_input( t_opts *opts, int argc, char **argv );

/* ft_nm */
int process_elf64( void *map );
int process_file( const char *filename, int fd, struct stat *st, void *map );
int ft_nm_wrapper( t_opts *opts );

#endif
