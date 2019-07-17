//
// Created by Yoshiko Harwyn hoare on 2019-07-03.
//

#include "../../headers/minishell.h"

int 		len_two_dim(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*helper_strtrim(char* line)
{
	char	*head;
	char	*tail;

	head = line;
	tail = line + strlen(line) - 1;
	while (*head == ' ')
		head++;
	while (*tail == ' ')
		tail--;
	*(tail + 1) = '\0';
	return (head);
}

void check_zombie()
{
	int status;
	int pid;
	int job_id;

	while ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED|WCONTINUED)) > 0)
	{
		if (WIFEXITED(status))
			set_process_status(pid, STATUS_DONE);
		else if (WIFSTOPPED(status))
			set_process_status(pid, STATUS_SUSPENDED);
		else if (WIFCONTINUED(status))
			set_process_status(pid, STATUS_CONTINUED);

		job_id = get_job_id_by_pid(pid);
		if (job_id > 0 && is_job_completed(job_id)) {
			print_job_status(job_id);
			remove_job(job_id);
		}
	}
}


int execute_builtin_command(process *proc)
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