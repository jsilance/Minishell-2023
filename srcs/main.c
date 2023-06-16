/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/16 09:21:22 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_error(int errnum, char *line, t_lst_cmd *cmd, char **env)
{
	if (env)
		ft_tab_free(env);
	if (line)
		free(line);
	if (cmd)
		ft_cmd_lst_clear(cmd);
	if (errnum)
		perror("minishell");
	unlink(".tmp");
	exit(errnum);
}

int	main(int argc, char **argv, char **env)
{
	t_base	base_var;

	(void)argc;
	(void)argv;
	base_var.env_cpy = ft_tabdup(env);
	while (1)
	{
		sig_handler(0);
		base_var.line = readline("minishell$ ");
		sig_handler(1);
		if (base_var.line == NULL)
		{
			printf("exit\n");
			exit(130);
		}
		if (!ft_strncmp(base_var.line, "./minishell ", 12))
			sig_handler(2);
		add_history(base_var.line);
		if (base_var.line && !ft_strncmp(base_var.line, "exit", 4))
			ft_error(g_sig_status, base_var.line, NULL, base_var.env_cpy);
		base_var.cmd_lst = ft_parsing(base_var.line, 0, 0, NULL);
		if (ft_pipe(base_var.cmd_lst) == -1)
			ft_error(2, base_var.line, base_var.cmd_lst, base_var.env_cpy);
		if (!base_var.env_cpy)
			ft_error(3, base_var.line, base_var.cmd_lst, base_var.env_cpy);
		ft_cmd_lst_execute(base_var.cmd_lst, &base_var.env_cpy);
		ft_cmd_lst_clear(base_var.cmd_lst);
		free(base_var.line);
		base_var.line = NULL;
	}
	ft_tab_free(base_var.env_cpy);
	return (0);
}

// ft_cmd_lst_print(base_var.cmd_lst);
