/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:48:00 by amandour          #+#    #+#             */
/*   Updated: 2024/09/10 02:14:27 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_heredoc_input(int fd_w, char *delimiter, t_shell *shell)
{
	char	*input_line;
	char	*exp_line;
	char	*tmp;

	signal(SIGINT, handle_signal_herdoc);
	while (1)
	{
		input_line = readline("> ");
		tmp = remove_q(delimiter);
		if (!input_line || ft_strcmp(tmp, input_line) == 0)
			break ;
		if (*input_line == '\0')
			write(fd_w, "", 0);
		else if (d_quoted_del(delimiter) || s_quoted_del(delimiter))
			write_fd(fd_w, input_line);
		else
		{
			exp_line = search_and_replace_env_var(input_line, shell->my_env);
			write_fd(fd_w, exp_line);
			free(exp_line);
		}
		(free(input_line), free(tmp));
	}
	free(input_line);
}

static int	open_heredoc(char **filename, char **name_fre, int *fd_w, int *fd_r)
{
	*name_fre = generate_unique_filename();
	*filename = ft_strjoin("/private/tmp/file_", *name_fre);
	free(*name_fre);
	*fd_w = open(*filename, O_CREAT | O_WRONLY, 0777);
	*fd_r = open(*filename, O_CREAT | O_RDONLY, 0777);
	if (*fd_w == -1 || *fd_r == -1)
		return (-1);
	unlink(*filename);
	return (0);
}

static int	process_redirection(t_cmd *cmd, t_shell *shell, int i, char *del)
{
	char	*filename;
	char	*name_fre;
	int		fd_w;
	int		fd_r;
	int		f;

	f = dup(0);
	heredoc_flag = 0;
	del = cmd->red[i + 1];
	if (open_heredoc(&filename, &name_fre, &fd_w, &fd_r) == -1)
		return (-1);
	handle_heredoc_input(fd_w, del, shell);
	if (heredoc_flag)
	{
		heredoc_flag = 0;
		dup2(f, 0);
		(close(f), close(fd_r));
		(close(fd_w), free(filename));
		return (-3);
	}
	close(fd_w);
	free(filename);
	cmd->fd_herdoc = fd_r;
	close(f);
	return (0);
}

int	ft_heredoc(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;
	int		check_hec;

	cmd = shell->head;
	while (cmd)
	{
		i = 0;
		while (cmd->red && cmd->red[i])
		{
			if (ft_strcmp(cmd->red[i], "<<") == 0 && cmd->red[i + 1])
			{
				check_hec = process_redirection(cmd, shell, i, cmd->red[i + 1]);
				if (check_hec == -3)
					return (-3);
				if (check_hec == -1)
					return (-1);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (1);
}
