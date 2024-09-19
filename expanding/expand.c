/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:09:33 by amandour          #+#    #+#             */
/*   Updated: 2024/09/18 17:55:34 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_wildcard(t_cmd *cmd, int *index)
{
	char	**wildcard_result;
	int		t_count;

	if (is_wildcard_quoted(cmd->cmd[*index]))
		return ;
	wildcard_result = get_wildcard_results(cmd->cmd[*index], &t_count);
	if (wildcard_result && t_count > 0)
	{
		insert_resul(cmd, wildcard_result, index, t_count);
		ft_free(wildcard_result);
	}
	else
		return ;
}


int	is_wildcard_quoted(char *str)
{
	int		s_quote;
	int		d_quote;
	int		i;

	(1) && (s_quote = 0, d_quote = 0, i = 0);
	while (str[i])
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[i] == '"' && !s_quote)
			d_quote = !d_quote;
		else if (str[i] == '*' && !s_quote && !d_quote)
			return (0);
		i++;
	}
	return (1);
}


// void expand_cmd(t_cmd *cmd, t_env *env) {
//     int i;

//     if (cmd->cmd && cmd->expd) {
//         i = 0;
//         // Première passe : traiter les variables d'environnement
//         while (cmd->cmd[i] && i < cmd->cmd_count) {
//             if (strchr(cmd->cmd[i], '$')) {
//                 proc_env_var(&cmd->cmd[i], env, &cmd->expd[i]);
//             }
//             i++;
//         }


//         i = 0;
//         while (cmd->cmd[i] && i < cmd->cmd_count) {
//             if (strchr(cmd->cmd[i], '*') && !is_wildcard_quoted((cmd->cmd[i]))) {
//                 // Remplacer cmd->cmd[i] par la liste de fichiers correspondants
//                 expand_wildcard(cmd, &i);
// 				i++;
// 				continue;

//             }
// 			else
//           	  i++;
//         }
//     }
// }

void	expand_cmd(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->cmd && cmd->expd)
	{
		i = 0;
		while (cmd->cmd[i] && i < cmd->cmd_count)
		{
			if (ft_strchr(cmd->cmd[i], '*') && !is_wildcard_quoted(cmd->cmd[i]))
			{
				expand_wildcard(cmd, &i);
			}
			if (ft_strchr(cmd->cmd[i], '$'))
			{
				proc_env_var(&cmd->cmd[i], env, &cmd->expd[i]);
				i++;
			}
			else
				i++;
		}
	}
}

void	expand_redirections(t_cmd *cmd, t_env *env)
{
	int	i;

	if (cmd->red)
	{
		i = 0;
		while (cmd->red[i])
		{
			if (!ft_strcmp(cmd->red[i], "<<"))
			{
				i += 2;
				continue ;
			}
			else if (!ft_strcmp(cmd->red[i], "*"))
			{
				ft_putstr_fd(cmd->red[i], 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				cmd->ambiguous_redirect = 1;
				return ;
			}
			else if (ft_strchr(cmd->red[i], '$'))
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
