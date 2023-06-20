/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:13:12 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/20 13:13:35 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_special_case(char *str)
{
	if (!ft_strcmp(str, "-") || !ft_strcmp(str, "'-'") || !ft_strcmp(str,
			"\"-\""))
	{
		free(str);
		return (ft_strdup("$OLDPWD"));
	}
	return (str);
}
