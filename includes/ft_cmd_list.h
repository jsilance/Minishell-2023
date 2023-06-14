/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:30:41 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/14 16:42:49 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_LIST_H
# define FT_CMD_LIST_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum					e_output_type
{
	DEFAULT = 1,
	PIPE,
	OVERWRITE,
	APPEND,
	READ,
	HERE_DOC
};
typedef struct s_lst_arg
{
	char				*content;
	int					len;
	struct s_lst_arg	*next;
}						t_lst_arg;

typedef struct s_lst_cmd
{
	struct s_lst_cmd	*next;
	t_lst_arg			*arguments;
	int					fd_in;
	int					fd_out;
	int					input_type;
	int					output_type;
}						t_lst_cmd;

t_lst_arg				*ft_list_new(char *content, int len);
t_lst_arg				*ft_lst_last(t_lst_arg *lst);
t_lst_arg				*ft_lst_add_back(t_lst_arg **lst, char *content,
							int len);
t_lst_arg				*ft_lst_clear(t_lst_arg *cmd);
size_t					ft_lst_size(t_lst_arg *lst);

t_lst_cmd				*ft_cmd_list_new(t_lst_arg *arg);
t_lst_cmd				*ft_cmd_lst_last(t_lst_cmd *lst);
t_lst_cmd				*ft_cmd_lst_add_back(t_lst_cmd **lst, t_lst_cmd *new);
t_lst_cmd				*ft_cmd_lst_clear(t_lst_cmd *lst);

void					ft_cmd_lst_print(t_lst_cmd *cmd);
char					**arg_to_tab(t_lst_arg *arg, char **env);

#endif
