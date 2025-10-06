#ifndef FT_NM_H
#define FT_NM_H


/* Includes */
#include "linked_list.h"


/* Structures */
typedef struct s_opts {
	int    flags;
	t_list *files;
	int    nb_files;
} t_opts;


/* Prototypes */
/* Parsing */
void parse_input( t_opts *opts, int argc, char **argv );

/* Tha function */
int ft_nm( t_opts *opts );


#endif
