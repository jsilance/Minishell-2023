/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/28 19:11:28 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error(char *str_error, int errnum, char *line, t_lst_cmd *cmd,
		char **env)
{
	if (env)
		ft_tab_free(env);
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
	char		**cpy_env;

	(void)argc;
	(void)argv;
	signal(SIGINT, sighandler);
	cpy_env = ft_tabdup(env);
	while (1)
	{
		line = readline("\033[0;36m$\033[0;32m ->\033[0m ");
		if (!line)
			ft_error("readline", 1, line, NULL, cpy_env);
		add_history(line);
		if (line && !ft_strncmp(line, "exit", 4))
			ft_error(NULL, 0, line, NULL, cpy_env);
		cmd_lst = ft_parsing(line);
		if (ft_pipe(cmd_lst) == -1)
			ft_error("ft_pipe", 2, line, cmd_lst, cpy_env);
		if (!cpy_env)
			ft_error("ft_tabdup", 3, line, cmd_lst, cpy_env);
		ft_cmd_lst_execute(cmd_lst, &cpy_env);
		ft_cmd_lst_clear(cmd_lst);
		free(line);
		line = NULL;
	}
	// ft_tab_free(cpy_env);
	// ft_error doit free cpy_env
	return (0);
}
