/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_kill_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:08:55 by sbearded          #+#    #+#             */
/*   Updated: 2019/07/26 15:32:45 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int		shell_kill_ext(pid_t pid, int job_id)
{
	if (kill(pid, SIGKILL) < 0)
	{
		ft_printf("21sh: kill %d: job not found\n", pid);
		return (0);
	}
	if (job_id > 0)
	{
		set_job_status(job_id, STATUS_TERMINATED);
		print_job_status(job_id);
		if (wait_for_job(job_id) >= 0)
			remove_job(job_id);
	}
	return (1);
}

int				shell_kill(t_process *proc)
{
	pid_t		pid;
	int			job_id;

	if (proc->query[1] == NULL)
	{
		ft_printf("usage: kill <pid>\n");
		return (-1);
	}
	job_id = -1;
	if (proc->query[1][0] == '%')
	{
		job_id = ft_atoi(proc->query[1] + 1);
		pid = get_pgid_by_job_id(job_id);
		if (pid < 0)
		{
			ft_printf("21sh: kill %s: no such job\n", proc->query[1]);
			return (-1);
		}
		pid = -pid;
	}
	else
		pid = ft_atoi(proc->query[1]);
	return (shell_kill_ext(pid, job_id));
}

int				check_built_in(t_process *proc)
{
	if (ft_strequ(proc->query[0], "exit")
		|| ft_strequ(proc->query[0], "cd")
		|| ft_strequ(proc->query[0], "setenv")
		|| ft_strequ(proc->query[0], "unsetenv")
		|| ft_strequ(proc->query[0], "jobs")
		|| ft_strequ(proc->query[0], "bg")
		|| ft_strequ(proc->query[0], "fg")
		|| ft_strequ(proc->query[0], "kill")
		|| ft_strequ(proc->query[0], "alias")
		|| ft_strequ(proc->query[0], "unalias")
		|| ft_strequ(proc->query[0], "set")
		|| ft_strequ(proc->query[0], "unset")
		|| ft_strequ(proc->query[0], "export")
		|| ft_strequ(proc->query[0], "fc")
		|| ft_strequ(proc->query[0], "echo"))
		return (1);
	else
		return (0);
}
