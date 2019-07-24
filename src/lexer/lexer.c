/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:54:35 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/23 15:54:36 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		get_command_type_(char *command)
{
	if (strcmp(command, "exit") == 0)
		return (COMMAND_EXIT);
	else if (strcmp(command, "help") == 0)
		return (COMMAND_HELP);
	else if (strcmp(command, "cd") == 0)
		return (COMMAND_CD);
	else if (strcmp(command, "jobs") == 0)
		return (COMMAND_JOBS);
	else if (strcmp(command, "fg") == 0)
		return (COMMAND_FG);
	else if (strcmp(command, "bg") == 0)
		return (COMMAND_BG);
	else if (strcmp(command, "kill") == 0)
		return (COMMAND_KILL);
	else if (strcmp(command, "export") == 0)
		return (COMMAND_EXPORT);
	else if (strcmp(command, "unset") == 0)
		return (COMMAND_UNSET);
	else
		return (COMMAND_EXTERNAL);
}

t_job	*init_job(void)
{
	t_job	*new_job;

	if ((new_job = (t_job*)malloc(sizeof(t_job))) == NULL)
		exit(1);
	new_job->pgid = -1;
	new_job->id = 0;
	new_job->mode = FOREGROUND_EXECUTION;
	return (new_job);
}

t_job	*lexer(char **arg)
{
	t_job		*new_job;
	t_process	*temp_process;
	int			i;

	new_job = init_job();
	i = 0;
	new_job->root = new_segment(arg, i);
	if (!(new_job->root))
		return (free_job(new_job));
	while (arg[i] && ft_strcmp(arg[i], "|"))
		++i;
	i += arg[i] ? 1 : 0;
	temp_process = new_job->root;
	while (arg[i])
	{
		if ((temp_process->next = new_segment(arg, i)) == NULL)
			return (free_job(new_job));
		while (arg[i] && ft_strcmp(arg[i], "|"))
			++i;
		i += arg[i] ? 1 : 0;
		temp_process = temp_process->next;
	}
	return (new_job);
}
