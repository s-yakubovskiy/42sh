/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:22:56 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 12:35:33 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			is_job_completed(int id)
{
	t_process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (0);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		if (proc->status != STATUS_DONE)
			return (0);
		proc = proc->next;
	}
	return (1);
}

int			print_processes_of_job(int id)
{
	t_process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	printf("[%d]", id);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		printf(" %d", proc->pid);
		proc = proc->next;
	}
	printf("\n");
	return (0);
}

static char	*get_state_string(t_process *proc)
{
	char	*state;

	if (proc->status == 0)
		state = strdup("running");
	else if (proc->status == 1)
		state = strdup("done");
	else if (proc->status == 2)
		state = strdup("suspended");
	else if (proc->status == 1)
		state = strdup("continued");
	else
		state = strdup("terminated");
	return (state);
}

int			print_job_status(int id)
{
	t_process *proc;
	char	*state;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	printf("[%d]", id);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		state = get_state_string(proc);
		printf("\t%d\t%s\t%s", proc->pid, state, proc->query[0]);
		if (proc->next != NULL)
			printf("|\n");
		else
			printf("\n");
		proc = proc->next;
		free(state);
	}
	return (0);
}

int			insert_job(t_job *job)
{
	int		id;

	id = get_next_job_id();
	if (id < 0)
		return (-1);
	job->id = id;
	shell->jobs[id] = job;
	return (id);
}