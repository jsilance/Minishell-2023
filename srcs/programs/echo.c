/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:39:43 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/29 14:56:01 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_str_var_process(char *str, char **env)
// {
// 	char	*ptr;

// 	ptr = NULL;
// 	while ()
// }

int	ft_echo(t_lst_arg *arg, char **env)
{
	int	no_newline;

	(void)env;
	no_newline = 0;
	if (ft_strncmp(arg->content, "echo", 5) != 32)
		return (-1);
	else
		arg = arg->next;
	if (arg && !ft_strncmp(arg->content, "-n", arg->len))
	{
		no_newline = 1;
		arg = arg->next;
	}
	while (arg)
	{
		if (arg && !(ft_strchr("\"", arg->content[-1]) && !ft_strchr(" ",
					arg->content[-2])))
			printf(" ");
		printf("%.*s", arg->len, arg->content);
		arg = arg->next;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
