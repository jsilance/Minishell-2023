/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/03 21:39:30 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_whitespace(char *line, int *i, int *len)
{
	*len = 0;
	while (line[*i] && ft_strchr(" ", line[*i]))
		(*i)++;
}

void	word_delimeter(char *line, int *i, int *len)
{
	while (line[*i + *len] && !ft_strchr(" ;|><", line[*i + *len]))
	{
		if (line[*i + *len] == '\"')
		{
			(*len)++;
			while (line[*i + *len] && line[*i + *len] != '\"')
				(*len)++;
			(*len)++;
		}
		else if (line[*i + *len] == '\'')
		{
			(*len)++;
			while (line[*i + *len] && line[*i + *len] != '\'')
				(*len)++;
			(*len)++;
		}
		else if (line[*i + *len])
			(*len)++;
	}
	if (*len == 0)
		while (line[*i + *len] && ft_strchr(">", line[*i + *len]))
			(*len)++;
	if (*len == 0)
		while (line[*i + *len] && ft_strchr("<", line[*i + *len]))
			(*len)++;
}

static int	output_type_selector(char *line)
{
	if (!line[0] || line[0] == ';')
		return (DEFAULT);
	else if (line[0] == '|')
		return (PIPE);
	else if (line[0] == '>' && line[1] == '>')
		return (APPEND);
	else if (line[0] == '>')
		return (OVERWRITE);
	return (-1);
}

t_lst_cmd	*ft_parsing(char *line, int i, int len, t_lst_cmd *cmd_lst)
{
	t_lst_cmd	*cmd;

	while (line && line[i])
	{
		cmd = ft_cmd_list_new(NULL);
		if (!cmd || !ft_cmd_lst_add_back(&cmd_lst, cmd))
			return (NULL);
		while (line[i] && !ft_strchr(";|", line[i]))
		{
			skip_whitespace(line, &i, &len);
			word_delimeter(line, &i, &len);
			if (line[i] == '|')
				break ;
			if (len > 0 && !ft_lst_add_back(&cmd->arguments, &line[i], len))
				return (ft_cmd_lst_clear(cmd_lst));
			i += len;
			if (line[i] == '"')
				i++;
			while (line[i] && line[i] == ' ')
				i++;
		}
		cmd->output_type = output_type_selector(&line[i]);
		i += (cmd->output_type == APPEND) + (line[i] != 0);
	}
	return (cmd_lst);
}
