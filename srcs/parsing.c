/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 15:39:51 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	string_delimeter(char *line, int *i, int *len)
// {
// 	if (line[*i] && line[*i] == '"')
// 	{
// 		while (line[*i + *len] != '"')
// 			(*len)++;
// 	}
// }

static void	skip_whitespace(char *line, int *i)
{
	while (line[*i] && line[*i] != '\n' && ft_strchr(" ", line[*i]))
		(*i)++;
}
void	word_delimeter(char *line, int *i, int *len)
{
	if (line[*i] && line[*i] == '"')
	{
		(*i)++;
		while (line[*i + *len] && line[*i + *len] != '"')
			(*len)++;
		return ;
	}
	while (line[*i + *len] && !ft_strchr(" ;|><\"\n", line[*i + *len]))
	{
		(*len)++;
	}
	if (*len == 0)
		while (line[*i + *len] && ft_strchr(">", line[*i + *len]))
			(*len)++;
	if (*len == 0)
		while (line[*i + *len] && ft_strchr("<", line[*i + *len]))
			(*len)++;
	if (*len == 0 && line[*i + *len] && line[*i + *len] == '$')
	{
		(*len)++;
		while (line[*i + *len] && !ft_strchr(" ;|><", line[*i + *len]))
			(*len)++;
	}
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

// char *word_to_arg()

t_lst_cmd	*ft_parsing(char *line)
{
	int			i;
	int			len;
	t_lst_cmd	*cmd_lst;
	t_lst_cmd	*cmd;

	cmd_lst = NULL;
	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		cmd = ft_cmd_list_new(NULL);
		if (!cmd || !ft_cmd_lst_add_back(&cmd_lst, cmd))
			return (NULL);
		while (line[i] && line[i] != '\n' && !ft_strchr(";|\n", line[i]))
		{
			len = 0;
			skip_whitespace(line, &i);
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
		if (cmd->output_type == 4)
			i++;
		i++;
	}
	return (cmd_lst);
}
