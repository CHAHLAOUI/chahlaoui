/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:43:41 by amandour          #+#    #+#             */
/*   Updated: 2024/09/12 22:46:01 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_output_redirection(char *filename, int append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit_stat(1);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_input_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit_stat(1);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

void	handle_heredoc(int fd_herdoc)
{
	dup2(fd_herdoc, STDIN_FILENO);
	close(fd_herdoc);
}

int	redirections(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->red && cmd->red[i])
	{
		if (cmd->ambiguous_redirect)
			return (0);
		if (strcmp(cmd->red[i], "<<") == 0 && cmd->red[i + 1])
			(handle_heredoc(cmd->fd_herdoc), i += 2);
		else if (strcmp(cmd->red[i], ">") == 0 && cmd->red[i + 1])
		{
			if (handle_output_redirection(cmd->red[i + 1], 0) == -1)
				return (0);
			i += 2;
		}
		else if (strcmp(cmd->red[i], ">>") == 0 && cmd->red[i + 1])
		{
			if (handle_output_redirection(cmd->red[i + 1], 1) == -1)
				return (0);
			i += 2;
		}
		else if (strcmp(cmd->red[i], "<") == 0 && cmd->red[i + 1])
		{
			if (handle_input_redirection(cmd->red[i + 1]) == -1)
				return (0);
			i += 2;
		}
		else
			i++;
	}
	return (1);
}
