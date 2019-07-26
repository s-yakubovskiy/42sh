/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:07:58 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/26 14:16:06 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void		check_zombie(void)
{
	int		status;
	int		pid;
	int		job_id;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (WIFEXITED(status))
			set_process_status(pid, STATUS_DONE);
		else if (WIFSTOPPED(status))
			set_process_status(pid, STATUS_SUSPENDED);
		else if (WIFCONTINUED(status))
			set_process_status(pid, STATUS_CONTINUED);
		job_id = get_job_id_by_pid(pid);
		if (job_id > 0 && is_job_completed(job_id))
		{
			print_job_status(job_id);
			remove_job(job_id);
		}
	}
}

int			execute_builtin_command(t_process *proc)
{
	if (proc->type == COMMAND_EXIT)
		exit_shell(proc);
	else if (proc->type == COMMAND_CD)
		cd_shell(proc);
	else if (proc->type == COMMAND_HELP)
		help_shell(proc);
	else if (proc->type == COMMAND_JOBS)
		shell_jobs(proc);
	else if (proc->type == COMMAND_FG)
		shell_fg(proc);
	else if (proc->type == COMMAND_BG)
		shell_bg(proc);
	else if (proc->type == COMMAND_KILL)
		shell_kill(proc);
	else
		return (0);
	return (1);
}

char		*str_join_her(char *s1, char *s2)
{
	char	*temp;

	if (!s1)
	{
		if (s2)
			return (ft_strdup(s2));
		return (ft_strdup("\n"));
	}
	if (s2)
	{
		temp = s1;
		s1 = ft_strjoin(s1, "\n");
		free(temp);
		temp = s1;
		s1 = ft_strjoin(s1, s2);
		free(temp);
	}
	else
	{
		temp = s1;
		s1 = ft_strjoin(s1, "\n");
		free(temp);
	}
	return (s1);
}
