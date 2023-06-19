/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:20:55 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/19 18:56:28 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_full_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && ((str[i] != '-' || str[i] != '+') && !str[i
				+ 1]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_lst_arg *arg, char **env)
{
	char *temp;
	char *str;
	int ret;

	ret = g_sig_status;
	if (!ft_strscmp(arg->content, "exit"))
		return (-1);
	else
		arg = arg->next;
	if (arg)
	{
		str = ft_strndup(arg->content, arg->len);
		if (!str)
			return (-1);
		temp = ft_str_var_process(str, env);
		if (!temp)
			return (-1);
		free(str);
		ft_putstr_fd("exit\n", 2);
		if (!is_full_digit(temp))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(temp, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free(temp);
			return (255);
		}
		if (arg->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			free(temp);
			return (-1);
		}
		ret = ft_atoi(temp);
		free(temp);
	}
	return (ret);
}