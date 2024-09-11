/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahlao <achahlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:39:36 by achahlao          #+#    #+#             */
/*   Updated: 2024/09/11 22:39:57 by achahlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_main(t_shell *shell)
{
	signal(SIGQUIT, signal_handler);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		shell->input = read_in_line();
		if (shell->input == NULL)
			break ;
		shell->args = ft_split(shell->input);
		if (!shell->args)
		{
			free(shell->input);
			shell->input = NULL;
			continue ;
		}
		shell->head = fill_nodes(shell->args);
		if (shell->head == NULL)
		{
			ft_free(shell->args);
			free(shell->input);
			shell->input = NULL;
			continue ;
		}
		signal(SIGINT, signal_handler);
		expanding(shell);
		remove_q_all_cmd(shell->head);
		process_cmd(shell->head);
		if (ft_heredoc(shell) == -3)	
			continue ;
		execution(shell);
		free_cmd(shell->head);
		ft_free(shell->args);
		free(shell->input); 
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	// shell.heredoc_fd = -1;
    shell.head = NULL;
	if (env == NULL || *env == NULL)
		return (write(2, "there is no env\n", 16), 1);
	rl_catch_signals = 0;
	if (init_env(env, &(shell.my_env)) == -1)
		return (-1);
	main_main(&shell);
	free_env_list(shell.my_env);
	// clear_history();
	return (0);
}
