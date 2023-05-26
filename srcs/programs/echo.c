/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:39:43 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 18:33:37 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_str_var_process(char *str, char **env)
// {
// 	char	*ptr;

// 	ptr = NULL;
// 	while ()
// }

int	ft_echo(t_lst_arg *arg)
{
	int	no_newline;

	no_newline = 0;
	if (ft_strncmp(arg->content, "echo", arg->len))
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
		printf("%.*s", arg->len, arg->content);
		arg = arg->next;
		if (arg && !(ft_strchr("\"", arg->content[-1]) && !ft_strchr(" ",
					arg->content[-2])))
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
