/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_addbegin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:28 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:29 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_addbegin(t_dlist **alst, t_dlist *new)
{
	if (alst && new)
	{
		if (*alst)
		{
			while ((*alst)->prev != NULL)
				*alst = (*alst)->prev;
			new->prev = NULL;
			new->next = *alst;
			(*alst)->prev = new;
		}
		*alst = new;
	}
}
