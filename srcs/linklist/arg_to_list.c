/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/24 19:39:18 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_delimeter(char *line, int *i, int *len)
{
	while (line[*i] && line[*i] != '\n' && ft_strchr(" ", line[*i]))
		(*i)++;
	while (line[*i + *len] && !ft_strchr(" ;|\n", line[*i + *len]))
		(*len)++;
}

t_lst_cmd	*ft_parsing(char *line)
{
	int			i;
	int			len;
	t_lst_cmd	*cmd_lst;
	t_lst_cmd	*cmd;

	cmd = NULL;
	cmd_lst = NULL;
	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		len = 0;
		cmd = ft_cmd_list_new(NULL);
		if (!cmd || !ft_cmd_lst_add_back(cmd_lst, cmd))
			return (NULL);
		while (!ft_strchr(";|\n", line[i]))
		{
			word_delimeter(line, &i, &len);
			if (len > 0 && !ft_lst_add_back(cmd->arguments, &line[i], len))
				return (ft_cmd_lst_clear(cmd_lst));
			i += len;
		}
		if (line[i] == '|')
			cmd->next_is_piped = TRUE;
		i++;
	}
	return (cmd);
}
