/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:43:07 by amandour          #+#    #+#             */
/*   Updated: 2024/09/18 23:15:59 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(int pipefds[][2], int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (pipe(pipefds[i]) == -1)
		{
			perror("pipe");
			break ;
		}
		i++;
	}
}

void	close_pipes(int pipefds[][2], int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		close(pipefds[i][0]);
		close(pipefds[i][1]);
		i++;
	}
}

void	wait_pro(t_info *info)
{
	pid_t	wpid;
	int		i;

	i = 0;
	while (i < info->n)
	{
		wpid = waitpid(info->pids[i], &info->shell->status, 0);
		if (WIFEXITED(info->shell->status))
		{
			exit_stat(WEXITSTATUS(info->shell->status));
		}
		else if (WIFSIGNALED(info->shell->status))
		{
			if (WTERMSIG(info->shell->status) == SIGINT)
				exit_stat(130);
			else if (WTERMSIG(info->shell->status) == SIGQUIT)
				exit_stat(131);
		}
		i++;
	}
	reset_redirections(info->saved_stdin, info->saved_stdout);
}

// {
// 	pid_t	wpid;
// 	int		i;

// 	i = 0;
// 	while (i < info->n)
// 	{
// 		wpid = waitpid(info->pids[i], &info->shell->status, 0);
// 		if (WIFEXITED(info->shell->status))
// 			exit_stat(WEXITSTATUS(info->shell->status));
// 		i++;
// 	}
// 	reset_redirections(info->saved_stdin, info->saved_stdout);
// }

void	init_info(t_info *info, t_shell *shell)
{
	info->pids = NULL;
	info->cmd = shell->head;
	info->shell = shell;
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
	info->n = cmd_size(info->cmd);
	if (info->n > 1)
		info->pipefd = (int (*)[2])malloc(sizeof(int [2]) * (info->n - 1));
	else
		info->pipefd = NULL;
	empty_args(info);
}

void	execution(t_shell *shell)
{
	t_info	info;
	int		i;
	pid_t	pid;

	(init_info(&info, shell), i = -1);
	if (info.n == 1 && check_builtin(info.cmd->cmd[0]))
		builtin(&info);
	else
	{
		create_pipes(info.pipefd, info.n);
		info.pids = malloc(sizeof(int) * info.n);
		if (!info.pids)
			return ;
		while (++i < info.n)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork: ");
				break ;
			}
			if (pid == 0)
				child_process(&info, i);
			info.pids[i] = pid;
			info.cmd = info.cmd->next;
		}
		(close_pipes(info.pipefd, info.n), wait_pro(&info));
	}
	(free(info.pipefd), free(info.pids));
}
