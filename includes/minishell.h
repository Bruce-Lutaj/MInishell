/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brulutaj <brulutaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:01:55 by chsassi           #+#    #+#             */
/*   Updated: 2024/10/08 15:21:07 by brulutaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec.h"
# include "libft.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_exit;

typedef struct s_env
{
	char			*var;
	char			*content;
	bool			is_hidden;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char			**cmd;
	char			**redirects;
	int				*pipe;
	int				fd_in; // start from -1
	int				fd_out; // start from -1
	int				cmd_id;
	char			*last_heredoc;
	struct s_shell	*next;
}	t_shell;

typedef struct s_all
{
	char	*input;
	t_shell	*shell;
	t_env	**env;
	int		cmd_nbr;
	int		restore_fd_in;
	int		restore_fd_out;
	int		status_code;
}	t_all;

// Init
void	check_input_loop(t_all *pAll);
int		process_input(t_all *pAll);
void	minishell_loop(t_env *env);

// Init Utils
int		input_check(t_all *pAll);
void	close_pipes_loop(int **pipex, int cmd_nbr);
// Waste
void	write_mtx2(char **mtx, int *arr);
char	*arr_int_str(int i);

#endif