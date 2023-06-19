/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:20:55 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/19 17:05:27 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	ft_exit(t_lst_arg *arg, char **env)
{
	char *temp;
	char *str;
	int ret;

	ret = 0;
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
		ret = ft_atoi(temp);
		free(temp);
		ft_putstr_fd("exit\n", 2);
		if (arg->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (-1);
		}
	}
	return (ret);
}