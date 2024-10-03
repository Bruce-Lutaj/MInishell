/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:05:35 by chsassi           #+#    #+#             */
/*   Updated: 2024/09/25 11:51:11 by chsassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_from_env(void/* t_all *pAll */)
{
	char	*env_path;
	char	**new_path;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	new_path = ft_split(env_path, ':');
	return (new_path);
}

//da cambiare command con ptr a struct;
char	*find_executable_in_env(char **paths, char *command)
{
	char		*full_path;
	char		*tmp;
	// const int	len = ft_strlen(command);

	if (ft_strchr(command, '/'))
	{
		if (!access(command, X_OK))
			return (ft_strdup(command));
		return (NULL);
	}
	while (paths && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

void	fork_cmd(char *cmd, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(cmd, args, envp) == -1)
			exit(127);
		exit(0);
	}
	else if (pid < 0)
		perror("Fork error");
	else
		waitpid(pid, &status, 0);
}

int	run_builtin(char **args, t_env **env_list) //da cambiare: accettera' la struct concordata
{
/* 	if (!ft_strcmp(args[0], "echo"))
		return (bin_echo(args), 1);
	else  */if (!ft_strcmp(args[0], "cd"))
		return (bin_cd(*env_list, args[1]), 1);
	else if (!ft_strcmp(args[0], "pwd"))
		return (bin_pwd(), 1);
	else if (!ft_strcmp(args[0], "export"))
		return (bin_export(env_list, args), 1);
	else if (!ft_strcmp(args[0], "unset"))
		return (bin_unset(env_list, args[1]), 1);
	else if (!ft_strcmp(args[0], "env"))
		return (bin_env(*env_list), 1);
	else if (!ft_strcmp(args[0], HEREDOC))
		return (handle_heredoc(args[1]), 1);
	// else if (!ft_strcmp(args[0], "exit"))
	// 	return (bin_exit(), 1);
	else
		return (0);
}

void	run_exec(t_env *env, char **args)
{
	char	*cmd_path;
	char	**paths;
	char	**env_mtx;

	if (!args || !args[0])
		return ;
	if (run_builtin(args, &env))
		return ;
	paths = get_path_from_env();
	cmd_path = find_executable_in_env(paths, args[0]);
	if (!cmd_path)
	{
		printf("%s: command not found\n", args[0]);
		g_exit = 127;
		free_mtx(paths);
		return ;
	}
	env_mtx = create_env_mtx(env);
	fork_cmd(cmd_path, args, env_mtx);
	free(cmd_path);
	free_mtx(env_mtx);
	free_mtx(paths);
}
