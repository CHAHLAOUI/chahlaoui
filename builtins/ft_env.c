/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:57:42 by amandour          #+#    #+#             */
/*   Updated: 2024/09/11 21:37:16 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *list)
{
	while (list)
	{
		if (list->key && list->value && list->value[0] != '\0')
			printf("%s=%s\n", list->key, remove_q(list->value));
		list = list->next;
	}
}
