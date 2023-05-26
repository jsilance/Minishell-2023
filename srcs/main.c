/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 19:32:18 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error(char *str_error, int errnum, char *line, t_lst_cmd *cmd)
{
	if (line)
		free(line);
	if (cmd)
		ft_cmd_lst_clear(cmd);
	if (errnum)
		perror(str_error);
	exit(errnum);
}

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
		line = readline("\033[0;36m$\033[0;32m ->\033[0m ");
		if (!line)
			ft_error("readline", 1, line, NULL);
		add_history(line);
		if (line && !ft_strncmp(line, "exit", 4))
			ft_error(NULL, 0, line, NULL);
		cmd_lst = ft_parsing(line);
		if (ft_pipe(cmd_lst) == -1)
			ft_error("ft_pipe", 2, line, cmd_lst);
		ft_cmd_lst_print(cmd_lst, env);
		ft_cmd_lst_clear(cmd_lst);
		free(line);
		line = NULL;
	}
	return (0);
}
