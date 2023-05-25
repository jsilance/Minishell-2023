/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/25 20:11:13 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_delimeter(char *line, int *i, int *len)
{
	while (line[*i] && line[*i] != '\n' && ft_strchr(" ", line[*i]))
		(*i)++;
	while (line[*i + *len] && !ft_strchr(" ;|>\n", line[*i + *len]))
		(*len)++;
}

void	ft_cmd_lst_print(t_lst_cmd *cmd)
{
	t_lst_arg	*ptr;

	while (cmd)
	{
		ptr = cmd->arguments;
		while (ptr)
		{
			printf("[%.*s]", ptr->len, ptr->content);
			ptr = ptr->next;
		}
		printf("(%i)\n", cmd->output_type);
		cmd = cmd->next;
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
		cmd = ft_cmd_list_new(NULL);
		if (!cmd || !ft_cmd_lst_add_back(&cmd_lst, cmd))
			return (NULL);
		while (line[i] && line[i] != '\n' && !ft_strchr(";|>\n", line[i]))
		{
			len = 0;
			word_delimeter(line, &i, &len);
			if (line[i] == '|')
				break ;
			if (len > 0 && !ft_lst_add_back(&cmd->arguments, &line[i], len))
				return (ft_cmd_lst_clear(cmd_lst));
			i += len;
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
