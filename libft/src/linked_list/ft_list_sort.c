/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:32:55 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/14 16:16:18 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void ft_list_sort( t_list **begin_list, int (*cmp)() )
{
	int    swapped;
	t_list *ptr;
	void   *tmp;
	t_list *end = NULL;	

	if ( !begin_list || !cmp || !*begin_list )
		return ;

	do {
		swapped = 0;
		ptr = *begin_list;

		while (ptr->next != end) {
			if (cmp(ptr->content, ptr->next->content) > 0) {
				tmp = ptr->content;
				ptr->content = ptr->next->content;
				ptr->next->content = tmp;
				swapped = 1;
			}
			ptr = ptr->next;
		}
		end = ptr;
	} while (swapped);
}
