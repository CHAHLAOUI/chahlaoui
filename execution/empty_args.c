/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:39:32 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 11:44:01 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

void	free_fil_args(char **filtered_cmd)
{
	int	i;

	if (!filtered_cmd)
		return ;
	i = 0;
	while (filtered_cmd[i])
	{
		free(filtered_cmd[i]);
		i++;
	}
	free(filtered_cmd);
}

char	**empty_args(char **cmd)
{
	char	**filt_cmd;
	int		i;
	int		j;
	int		count;

	(1) && (i = 0, count = 0);
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
			count++;
		i++;
	}
	filt_cmd = malloc((count + 1) * sizeof(char *));
	if (!filt_cmd)
		return (NULL);
	(1) && (j = 0, i = 0);
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
			filt_cmd[j++] = ft_strdup(cmd[i]);
		i++;
	}
	filt_cmd[j] = NULL;
	return (filt_cmd);
}
