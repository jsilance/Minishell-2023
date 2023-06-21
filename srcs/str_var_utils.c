/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:36:15 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/21 11:36:20 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	home_checker(char *arg, size_t *i, char **ptr, char **env)
{
	if (arg[*i] == '~')
	{
		if (!arg[(*i) + 1] || (arg[(*i) + 1] && arg[*i + 1] == '/'))
		{
			*ptr = ft_strnstock(*ptr, var_to_str("HOME", env, i), -1, 3);
			*i -= 3;
		}
	}
}
