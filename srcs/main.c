/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:35:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 17:05:47 by jusilanc         ###   ########.fr       */
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
	unlink(".tmp");
	if (errnum == 130)
	{
		printf("exit\n");
		exit(130);
	}
	if (errnum)
		perror("minishell");
	exit(errnum);
}

void	shell_level(char **env)
{
	int		i;
	char	*temp;
	char	*old_var;
	long	shlvl;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL", 5))
		{
			old_var = env[i];
			temp = ft_strchr(env[i], '=') + 1;
			shlvl = ft_atoi(temp);
			if (shlvl < 0)
				shlvl = 0;
			else
				shlvl++;
			env[i] = ft_strnstock("SHLVL=", ft_itoa(shlvl), -1, 2);
			free(old_var);
		}
		i++;
	}
}

void	free_loop(t_base base_var)
{
	unlink(".tmp");
	ft_cmd_lst_clear(base_var.cmd_lst);
	free(base_var.line);
}

void	pipe_creator(t_base base_var)
{
	if (ft_pipe(base_var.cmd_lst) == -1)
		ft_error(2, base_var.line, base_var.cmd_lst, base_var.env_cpy);
	if (!base_var.env_cpy)
		ft_error(3, base_var.line, base_var.cmd_lst, base_var.env_cpy);
}

int	main(int argc, char **argv, char **env)
{
	t_base	base_var;

	(void)argc;
	(void)argv;
	base_var.env_cpy = ft_tabdup(env);
	if (!base_var.env_cpy)
		ft_error(1, NULL, NULL, NULL);
	shell_level(base_var.env_cpy);
	while (1)
	{
		sig_handler(0);
		base_var.line = readline("minishell$ ");
		sig_handler(1);
		if (base_var.line == NULL)
			ft_error(130, NULL, NULL, base_var.env_cpy);
		if (!ft_strncmp(base_var.line, "./minishell ", 12))
			sig_handler(2);
		add_history(base_var.line);
		base_var.cmd_lst = ft_parsing(base_var.line, 0, 0, NULL);
		pipe_creator(base_var);
		ft_cmd_lst_execute(base_var.cmd_lst, &base_var.env_cpy);
		free_loop(base_var);
	}
	ft_tab_free(base_var.env_cpy);
	return (1);
}
