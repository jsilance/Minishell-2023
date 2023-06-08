/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:05:46 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/08 21:28:33 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_lst_arg *arg, char **env)
{
	char	path_str[4096];
	char	*temp;

	if (ft_strncmp(arg->content, "pwd", arg->len))
		return (-1);
	path_str[0] = 0;
	if (!getcwd(path_str, 4096))
	{
		temp = ft_str_var_process("$PWD", env);
		ft_strlcpy(path_str, temp, ft_strlen(temp));
		free(temp);
	}
	printf("%s\n", path_str);
	return (0);
}
