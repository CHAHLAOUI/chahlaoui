/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_execution1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 01:35:19 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 20:51:29 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_command_path(char *command, t_env *env)
{
	char	*path;

	if (command[0] == '/' || strncmp(command, "./", 2) == 0)
		path = ft_strdup(command);
	else
		path = get_path(command, env_to_tab(env));
	// printf("path--> %s\n", path);
	return (path);
}

void	put_erroor_126(char *mini, char *path, char *err)
{
	ft_putstr_fd(mini, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(err, 2);
	exit_stat(126);
	exit(126);
}

void	put_erroor_127(char *mini, char *path, char *err)
{
	ft_putstr_fd(mini, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(err, 2);
	exit_stat(127);
	exit(127);
}

void	execute_path(char *path, t_cmd *cmd, t_env *env)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			if (is_directory(path))
				put_erroor_126("minishell:", path, ": Is a directory\n" );
			redirections(cmd);
			execve(path, cmd->cmd, env_to_tab(env));
			if (errno == ENOEXEC)
				put_erroor_126("minishell:", path, ": Exec format error \n" );
			perror("execve");
			exit_stat(126);
			exit(126);
		}
		else
		{
			fprintf(stderr, "minishell: %s: Permission denied\n", path);
			exit_stat(126);
			exit(126);
		}
	}
	else
		put_erroor_126("minishell:", path, ":command not found \n" );
}

void	execute_command(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	*command;
	char	**filter_cmd;

	filter_cmd = empty_args(cmd->cmd);
	if (!filter_cmd || !filter_cmd[0])
	{
		free(filter_cmd);
		return ;
	}
	command = ft_strdup(filter_cmd[0]);
	if (is_all_spaces(command))
		exec_command_not_found(command);
	path = handle_command_path(command, env);
	if (path)
	{
		cmd->cmd = filter_cmd;
		execute_path(path, cmd, env);
		if (path != command)
			free(path);
	}
	else
		exec_command_not_found(command);
	(free(command), free_fil_args(filter_cmd));
	exit(EXIT_FAILURE);
}
