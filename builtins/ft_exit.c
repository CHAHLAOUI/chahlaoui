/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:20:43 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 22:59:12 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long int	process_digits(const char *nbr, size_t *i)
{
	long int	result;

	result = 0;
	while (nbr[*i])
	{
		if (ft_isdigit(nbr[*i]))
		{
			if (result > (LONG_MAX - (nbr[*i] - '0')) / 10)
				return (-1);
			result = result * 10 + (nbr[*i] - '0');
		}
		else
			return (-1);
		(*i)++;
	}
	return (result);
}

static long int	ft_atoi(char *nb)
{
	long int	result;
	size_t		i;
	int			sign;
	bool		has_digits;
	char		*nbr;

	i = 0;
	sign = 1;
	has_digits = false;
	nbr = trim_espace(nb);
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	result = process_digits(nbr, &i);
	if (result == -1 || result == 0)
		return (-1);
	result *= sign;
	if (result > LONG_MAX || result < LONG_MIN)
		return (free(nbr), -1);
	free(nbr);
	return (mod(result));
}

void	exit_st(int nbr)
{
	exit_stat(nbr);
	exit(nbr);
}

void	put_exit(char *mini, char *path, char *err)
{
	ft_putstr_fd(mini, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(err, 2);
	exit_st(255);
}

void	ft_exit(t_cmd *cmd)
{
	size_t		nbr_arg;
	long int	num;
	t_cmd		*tmp;

	(1) && (tmp = cmd, num = 1);
	if (is_last_command_exit(tmp))
	{
		while (tmp->next)
			tmp = tmp->next;
		nbr_arg = compte_arg(tmp->cmd);
		if (nbr_arg >= 2)
			num = ft_atoi(tmp->cmd[1]);
		else
			exit(exit_stat(-1));
		if (nbr_arg > 2 && num != -1)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit_stat(1);
			return ;
		}
		else if (num == -1)
			put_exit("mini:exit:", tmp->cmd[1], ":numeric argument required\n");
		(exit_stat(num), exit(num));
	}
}
