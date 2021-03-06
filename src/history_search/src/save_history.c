/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <anorjen@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:42:33 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/16 16:32:28 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

int	save_history(void)
{
	int		fd;
	char	*file;

	file = replace_dir(ft_strdup(HISTORY_FILE), g_sh->env);
	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH)) != -1)
	{
		g_h_session = list_rewind_to_begin(g_h_session);
		while (g_h_session->down)
		{
			write(fd, g_h_session->line, ft_strlen(g_h_session->line));
			write(fd, "\n\n", 2);
			g_h_session = g_h_session->down;
		}
		close(fd);
		free(file);
		return (0);
	}
	free(file);
	return (-1);
}
