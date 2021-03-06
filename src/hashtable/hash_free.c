/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:44:10 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:44:11 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void			hash_free_item(t_buck_cont *item, const char *str,
						t_hashtable *table, void (*free_f)(void *))
{
	if (item == NULL)
		item = hash_remove(str, table);
	if (free_f)
		free_f(item->data);
	else
		free(item->data);
	free(item->key);
	free(item);
}

void			hash_clean_table(t_hashtable *table, void (*free_f)(void *))
{
	t_buck_cont		*bucket;
	t_buck_cont		*item;
	int				i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < table->nbuckets)
	{
		bucket = table->bucket_array[i];
		while (bucket)
		{
			item = bucket;
			bucket = bucket->next;
			hash_free_item(item, NULL, NULL, free_f);
		}
		table->bucket_array[i] = NULL;
		i++;
	}
	table->nentries = 0;
}

void			hash_free_table(t_hashtable *table)
{
	free(table->bucket_array);
	free(table);
}

void			hash_delete_table(t_hashtable *table, void (*free_f)(void *))
{
	hash_clean_table(table, free_f);
	hash_free_table(table);
}
