/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:48:38 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/09 23:45:13 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red(char c)
{
	return (c == '>' || c == '<');
}

int	ft_parsing(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (check_q_p(line) == -1)
		return (-1);
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (i == 0 || line[i + 1] == '\0')
				return (-1);
		}
		if (line[len - 1] == '|' && len > 0)
			return (-1);
		if (check_red_out(line, &i) == -1)
			return (-1);
		if (check_red_in(line, &i) == -1)
			return (-1);
		i++;
	}
	return (1);
}

char	*ft_strstr(char *src, char *rech)
{
	int	i;
	int	j;

	i = 0;
	if (rech[0] == '\0')
		return (src);
	while (src[i] != '\0')
	{
		j = 0;
		while (src[i + j] != '\0' && src[i + j] == rech[j])
		{
			if (rech[j + 1] == '\0')
				return (&src[i]);
			++j;
		}
		++i;
	}
	return (0);
}
