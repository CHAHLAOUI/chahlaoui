/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:22 by achahlao          #+#    #+#             */
/*   Updated: 2024/08/06 17:08:24 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd_list(t_cmd *head)
{
	int		i;
	t_cmd	*temp;

	temp = head;
	while (temp)
	{
		printf("Commandes:\n");
		i = 0;
		if (temp->cmd)
		{
			while (temp->cmd[i])
				(printf("  cmd[%d]: %s\n", i, temp->cmd[i]), i++);
		}
		printf("Red\n");
		i = 0;
		if (temp->red)
		{
			while (temp->red[i])
				(printf("  red[%d]: %s\n", i, temp->red[i]), i++);
		}
		temp = temp->next;
	}
}

int	init_env(char **env, t_env **new_env)
{
	*new_env = NULL;
	if (ft_get_env(env, new_env) == -1)
		return (-1);
	return (0);
}
