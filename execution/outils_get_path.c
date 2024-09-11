/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_get_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:42:29 by amandour          #+#    #+#             */
/*   Updated: 2024/09/11 21:42:30 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	ft_strchar(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (1);
		i--;
	}
	return (0);
}

char	*valid_path(char *path_value, char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		j;

	paths = splite(path_value, ':');
	if (paths == NULL)
		return (NULL);
	j = 0 ;
	while (paths[j])
	{
		tmp = ft_strjoin(paths[j], "/");
		if (!tmp)
			exit(1);
		path = ft_strjoin(tmp, cmd);
		if (!path)
			exit(1);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (ft_freee(paths), path);
		free(path);
		j++;
	}
	ft_freee(paths);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;

	i = 0 ;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (valid_path(env[i] + 5, cmd));
		i++;
	}
	if (ft_strchar(cmd, '/'))
		printf("minishell: %s: No such file or directory\n", cmd);
	else
		printf("minishell: %s: No such file or directory\n", cmd);
	exit(EXIT_FAILURE);
	return (NULL);
}
