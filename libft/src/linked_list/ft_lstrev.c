/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:08:07 by ebonutto          #+#    #+#             */
/*   Updated: 2025/10/16 12:25:05 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void ft_lstrev( t_list **lst )
{
	t_list *prev, *curr, *next;

	if ( !lst || !*lst )
		return ;

	prev = NULL;
	curr = *lst;
	while ( curr )
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*lst = prev;
}
