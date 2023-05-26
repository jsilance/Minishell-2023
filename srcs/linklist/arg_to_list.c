/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:01:47 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 13:25:03 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_delimeter(char *line, int *i, int *len)
{
	while (line[*i] && line[*i] != '\n' && ft_strchr(" ", line[*i]))
		(*i)++;
	while (line[*i + *len] && !ft_strchr(" ;|>\n", line[*i + *len]))
		(*len)++;
	if (*len == 0)
		while (line[*i + *len] && ft_strchr(">", line[*i + *len]))
			(*len)++;
	if (*len == 0)
		while (line[*i + *len] && ft_strchr("<", line[*i + *len]))
			(*len)++;
}

void	ft_execute(char *cmd, char **all_args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd, all_args, env);
	wait(0);
}

void	ft_cmd_lst_print(t_lst_cmd *cmd, char **env)
{
	t_lst_arg	*ptr;
	int			first;
	char		*path_cmd;
	char		*cmd_str;

	while (cmd)
	{
		first = TRUE;
		ptr = cmd->arguments;
		while (ptr)
		{
			if (first == TRUE)
			{
				cmd_str = ft_strndup(ptr->content, ptr->len);
				path_cmd = cmd_path(cmd_str, ft_path_finder(env));
				if (!path_cmd)
					printf("minishell: %s: %s\n", cmd_str, "command not found");
				else
					ft_execute(path_cmd, arg_to_tab(ptr), env);
				free(cmd_str);
				// utile pour execve mais free ici pour eviter les leaks
				free(path_cmd);
				first = FALSE;
			}
			// printf("[%.*s]", ptr->len, ptr->content);
			ptr = ptr->next;
		}
		// printf("(%i)\n", cmd->output_type);
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
		while (line[i] && line[i] != '\n' && !ft_strchr(";|\n", line[i]))
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
