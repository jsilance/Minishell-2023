/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/23 19:27:21 by jusilanc         ###   ########.fr       */
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
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, sighandler);
	while (1)
	{
		printf("\033[0;36m$\033[0;32m ->\033[0m ");
		line = readline(NULL);
		add_history(line);
		if (ft_strnstr(line, "exit", 4))
			exit(0);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
