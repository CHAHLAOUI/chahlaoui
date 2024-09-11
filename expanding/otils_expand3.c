/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otils_expand3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:42:11 by amandour          #+#    #+#             */
/*   Updated: 2024/09/11 21:42:12 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *src, int n)
{
	char	*new;
	int		i;
	int		len;

	len = 0;
	while (src[len] && len < n)
		++len;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	is_single_quotes(char *str, char *pos)
{
	char	*current;
	int		s_quote;
	int		d_quote;

	(1) && (current = str, s_quote = 0, d_quote = 0);
	while (current < pos)
	{
		if (*current == '"' && !s_quote)
			d_quote = !d_quote;
		else if (*current == '\'' && !d_quote)
			s_quote = !s_quote;
		current++;
	}
	if (s_quote)
		return (1);
	return (0);
}

int	compare_pos1(char *str)
{
	int	pos_equal;
	int	pos_dollar;
	int	i;

	(1) && (pos_equal = -1, pos_dollar = -1, i = 0);
	while (str[i] != '\0')
	{
		if (str[i] == '=' && pos_equal == -1)
			pos_equal = i;
		if (str[i] == '$' && pos_dollar == -1)
			pos_dollar = i;
		i++;
	}
	if (pos_equal == -1 || pos_dollar == -1)
		return (1);
	if (pos_equal < pos_dollar)
		return (0);
	else
		return (1);
}
