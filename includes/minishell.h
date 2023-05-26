/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:33 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 17:26:51 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_cmd_list.h"
# include "ft_programs.h"
# include "libft.h"

enum		e_bool
{
	FALSE = 0,
	TRUE
};

t_lst_cmd	*ft_parsing(char *line);

char		**ft_path_finder(char **env);
char		*cmd_path(char *cmd, char **path);
char		**ft_multi_free(char **ptr, size_t len);
int			ft_pipe(t_lst_cmd *cmd);

#endif
