/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:30:41 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/23 20:42:35 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_LIST_H
# define FT_CMD_LIST_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_lst_cmd
{
	char				*content;
	int					len;
	struct s_lst_cmd	*next;
}						t_lst_cmd;

t_lst_cmd				*ft_list_new(char *content, int len);
t_lst_cmd				*ft_lst_last(t_lst_cmd *lst);
t_lst_cmd				*ft_lst_add_back(t_lst_cmd *lst, char *content,
							int len);
t_lst_cmd				*ft_lst_clear(t_lst_cmd *cmd);
t_lst_cmd				*ft_parsing(char *line);

#endif
