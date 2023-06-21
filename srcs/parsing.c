/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:28:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 22:43:54 by jusilanc         ###   ########.fr       */
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
		if (line[*i + *len] == '\"' && ++(*len))
		{
			while (line[*i + *len] && line[*i + *len] != '\"')
				(*len)++;
			if (line[*i + *len])
				(*len)++;
		}
		else if (line[*i + *len] == '\'' && ++(*len))
		{
			while (line[*i + *len] && line[*i + *len] != '\'')
				(*len)++;
			if (line[*i + *len])
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

static void	rm_redir_lst(t_lst_cmd *cmd)
{
	t_lst_arg	*arg;
	t_lst_arg	*arg_prev;
	size_t		len;
	size_t		i;

	arg_prev = NULL;
	while (cmd)
	{
		i = 0;
		arg = cmd->arguments;
		len = ft_lst_size(arg);
		while (arg && i++ < len)
			parsing_main_part(&arg, &cmd, &arg_prev);
		cmd = cmd->next;
	}
}

static void	ft_parsing_ext(int *i, int *len, char *line, t_lst_cmd *cmd)
{
	*i += *len;
	if (line[*i] == '"')
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (line[*i] && cmd->arguments
		&& ft_strscmp(ft_lst_last(cmd->arguments)->content, "<"))
		cmd->input_type = READ;
	else if (line[*i] && cmd->arguments
		&& ft_strscmp(ft_lst_last(cmd->arguments)->content, "<<"))
		cmd->input_type = HERE_DOC;
	else if (line[*i] && cmd->arguments
		&& ft_strscmp(ft_lst_last(cmd->arguments)->content, ">"))
		cmd->output_type = OVERWRITE;
	else if (line[*i] && cmd->arguments
		&& ft_strscmp(ft_lst_last(cmd->arguments)->content, ">>"))
		cmd->output_type = APPEND;
	rm_redir_lst(cmd);
}

t_lst_cmd	*ft_parsing(char *line, int i, int len, t_lst_cmd *cmd_lst)
{
	t_lst_cmd	*cmd;

	while (line && line[i] && line[i] == ' ')
		i++;
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
			ft_parsing_ext(&i, &len, line, cmd);
		}
		if (line[i] == '|')
			cmd->output_type = output_type_selector(&line[i]);
		i += (line[i] && cmd->output_type == APPEND) + (line[i] != 0);
	}
	return (cmd_lst);
}
