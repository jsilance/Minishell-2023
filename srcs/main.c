/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 13:25:56 by jusilanc         ###   ########.fr       */
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
		if (ft_strnstr(line, "exit", 4))
			exit(0);
		// printf("%s\n", line);
		cmd_lst = ft_parsing(line);
		ft_cmd_lst_print(cmd_lst, env);
		ft_cmd_lst_clear(cmd_lst);
		free(line);
	}
	return (0);
}
