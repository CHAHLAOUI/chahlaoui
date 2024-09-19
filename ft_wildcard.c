/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:03:32 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/12 20:37:45 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*niveau;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (strdup(s2));
	niveau = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!niveau)
		return (NULL);
	while (s1[i] != '\0')
	{
		niveau[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		niveau[i] = s2[j];
		i++;
		j++;
	}
	niveau[i] = '\0';
	return (niveau);
}

static void	sort_words(char **words)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (words[i])
	{
		j = i + 1;
		while (words[j])
		{
			if (strcmp(words[i], words[j]) > 0)
			{
				temp = words[j];
				words[j] = words[i];
				words[i] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	*concatenate_words(char **words)
{
	char	*result;
	char	*temp;
	int		i;

	result = strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (words[i])
	{
		temp = ft_strjoin1(result, words[i]);
		free(result);
		result = temp;
		temp = ft_strjoin1(result, " ");
		free(result);
		result = temp;
		i++;
	}
	if (strlen(result) > 0)
		result[strlen(result) - 1] = '\0';
	return (result);
}

char	*sort_wildcard(char *dir)
{
	char	**words;
	char	*sorted_result;
	int		i;

	words = splite(dir, ' ');
	free(dir);
	if (!words)
		return (NULL);
	sort_words(words);
	sorted_result = concatenate_words(words);
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (sorted_result);
}

char	*ft_wildcard(char *dirname)
{
	struct dirent	*current;
	DIR				*dir;
	char			*temp_path;
	char			*path;

	dir = opendir(dirname);
	if (!dir)
		return (perror("Error opening directory"), NULL);
	(1) && (current = readdir(dir), path = ft_strdup(""));
	while (current)
	{
		if (ft_strncmp(current->d_name, ".", 1) == 0)
		{
			current = readdir(dir);
			continue ;
		}
		temp_path = ft_strjoin(path, current->d_name);
		free(path);
		path = temp_path;
		temp_path = ft_strjoin(path, " ");
		free(path);
		path = temp_path;
		current = readdir(dir);
	}
	return (closedir(dir), sort_wildcard(path));
}
