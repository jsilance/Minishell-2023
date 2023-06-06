/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:33 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/06 15:27:20 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_cmd_list.h"
# include "ft_programs.h"
# include "libft.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

enum			e_bool
{
	FALSE = 0,
	TRUE
};

typedef struct s_base
{
	char		*line;
	char		**env_cpy;
	t_lst_cmd	*cmd_lst;
	int			status;
}				t_base;

t_lst_cmd		*ft_parsing(char *line, int i, int len, t_lst_cmd *cmd_lst);

char			**ft_path_finder(char **env);
char			*cmd_path(char *cmd, char **path);
char			**ft_multi_free(char **ptr, size_t len);
char			**ft_tab_free(char **ptr);

int				ft_pipe(t_lst_cmd *cmd);
void			sig_handler(int signum);
void			all_signal(void);

#endif
