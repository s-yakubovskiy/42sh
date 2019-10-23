/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:05:03 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/05 18:27:36 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DLIST_H
# define FT_DLIST_H

# include "libft.h"

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist				*ft_dlist_new(void const *content, size_t content_size);
void				ft_dlist_add(t_dlist **alst, t_dlist *new);
void				ft_dlist_addback(t_dlist **alst, t_dlist *new);
void				ft_dlist_addbegin(t_dlist **alst, t_dlist *new);
size_t				ft_dlist_size(t_dlist *lst);
t_dlist				*ft_dlist_rewind(t_dlist *dlist);
void				ft_dlist_delone(t_dlist **lst);
void				ft_dlist_del(t_dlist **lst);

#endif