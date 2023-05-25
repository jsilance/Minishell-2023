/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:33 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/25 20:39:23 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_cmd_list.h"
# include "libft.h"

enum		e_bool
{
	FALSE = 0,
	TRUE
};

t_lst_cmd	*ft_parsing(char *line);

char		**ft_path_finder(char **env);
char		*cmd_path(char *cmd, char **path);
void		ft_multi_free(char **ptr);

#endif
