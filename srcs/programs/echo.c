/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:39:43 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/04 01:22:42 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	n_option(char *arg, size_t arg_len)
{
	size_t	i;

	i = 0;
	while (ft_strchr("'\"", arg[i]))
		i++;
	if (arg[i++] == '-')
	{
		while (arg[i] == 'n' && i < arg_len)
			i++;
		if (ft_strchr("\"'n", arg[i - 1]))
			if ((ft_strchr("\"'", arg[i]) || (arg[i] == ' ' && i == arg_len)))
				return (1);
	}
	return (0);
}

static void	ft_echo_processing(t_lst_arg *arg, char **env, int *is_first)
{
	char	*string_arg;
	char	*str;

	str = NULL;
	if (arg && !(ft_strchr("\"", arg->content[-1]) && !ft_strchr(" ",
				arg->content[-2])) && !*is_first)
		printf(" ");
	string_arg = ft_substr(arg->content, 0, arg->len);
	str = ft_str_var_process(string_arg, env);
	*is_first = 0;
	if (str)
		printf("%s", str);
	else
		*is_first = 1;
	free(str);
	free(string_arg);
}

int	ft_echo(t_lst_arg *arg, char **env)
{
	int	no_newline;
	int	is_first;

	is_first = 1;
	no_newline = 0;
	if (ft_strncmp(arg->content, "echo", 5) != 32)
		return (-1);
	else
		arg = arg->next;
	while (arg && n_option(arg->content, arg->len))
	{
		no_newline = 1;
		arg = arg->next;
	}
	while (arg)
	{
		ft_echo_processing(arg, env, &is_first);
		arg = arg->next;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
