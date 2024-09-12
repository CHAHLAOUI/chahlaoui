/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:09:33 by amandour          #+#    #+#             */
/*   Updated: 2024/09/12 20:04:21 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	proc_env_var(char **str, t_env *env, int *expand)
{
	char	*value;

	if (compare_pos1(*str) && !check_quotes1(*str))
		*expand = 1;
	value = search_and_replace_env_var(*str, env);
	if (value == NULL)
		return ;
	if (ft_strcmp(value, "") == 0)
	{
		free(*str);
		*str = ft_strdup("");
		*expand = 2;
	}
	else
	{
		free(*str);
		*str = ft_strdup(value);
	}
	free(value);
}

void	expand_wildcard(t_cmd *cmd, int index)
{
	char	*wild_str;
	char	**wildcard_result;
	int		j;
	int		t_count;

	(1) && (wild_str = ft_wildcard("."), t_count = 0, j = 0);
	if (wild_str)
	{
		wildcard_result = splite(wild_str, ' ');
		if (cmd->cmd[index])
			(free(cmd->cmd[index]), cmd->cmd[index] = NULL);
		if (wildcard_result)
		{
			while (wildcard_result[t_count])
				t_count++;
			cmd->cmd = realloc(cmd->cmd, sizeof(char *) * \
				(cmd->cmd_count + t_count + 1));
			if (!cmd->cmd)
				(perror("Failed malloc memory"), exit(EXIT_FAILURE));
			while (wildcard_result[j])
				(1) && (cmd->cmd[index + j] = wildcard_result[j], j++);
			cmd->cmd[index + j] = NULL;
		}
		(free(wildcard_result), free(wild_str));
	}
}

void	expand_cmd(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->cmd && cmd->expd)
	{
		i = 0;
		while (cmd->cmd[i] && i < cmd->cmd_count)
		{
			if (!strcmp(cmd->cmd[i], "*"))
				expand_wildcard(cmd, i);
			else if (ft_strchr(cmd->cmd[i], '$'))
				proc_env_var(&cmd->cmd[i], env, &cmd->expd[i]);
			i++;
		}
	}
}

void	expand_redirections(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->red && cmd->expd)
	{
		i = 0;
		while (cmd->red[i] && i < cmd->red_count)
		{
			if (ft_strchr(cmd->red[i], '$'))
			{
				proc_env_var(&cmd->red[i], env, &cmd->expd[cmd->cmd_count + i]);
				if (ft_count_w(cmd->red[i], ' ') > 1 || \
					!ft_strcmp(cmd->red[i], ""))
				{
					ft_putstr_fd(cmd->red[i], 2);
					ft_putstr_fd(": ambiguous redirect\n", 2);
					cmd->ambiguous_redirect = 1;
					return ;
				}
			}
			i++;
		}
	}
}

void	expanding(t_shell *shell)
{
	t_cmd	*tmp;
	int		total;

	tmp = shell->head;
	while (tmp)
	{
		tmp->cmd_count = 0;
		while (tmp->cmd && tmp->cmd[tmp->cmd_count])
			tmp->cmd_count++;
		tmp->red_count = 0;
		while (tmp->red && tmp->red[tmp->red_count])
			tmp->red_count++;
		total = tmp->cmd_count + tmp->red_count;
		tmp->expd = ft_calloc(total, sizeof(int));
		if (!tmp->expd)
		{
			ft_putstr_fd("memory allocation en error \n", 2);
			exit(1);
		}
		expand_cmd(tmp, shell->my_env);
		expand_redirections(tmp, shell->my_env);
		tmp = tmp->next;
	}
}
