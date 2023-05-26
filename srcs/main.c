/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 18:16:57 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int signum)
{
	(void)signum;
	printf("\n");
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_lst_cmd	*cmd_lst;

	(void)argc;
	(void)argv;
	signal(SIGINT, sighandler);
	while (1)
	{
		printf("\033[0;36m$\033[0;32m ->\033[0m ");
		line = readline(NULL);
		add_history(line);
		if (!ft_strncmp(line, "exit", 4))
			exit(0);
		cmd_lst = ft_parsing(line);
		if (cmd_lst->output_type == PIPE)
		{
			ft_pipe(cmd_lst);
		}
		ft_cmd_lst_print(cmd_lst, env);
		ft_cmd_lst_clear(cmd_lst);
		free(line);
	}
	return (0);
}
