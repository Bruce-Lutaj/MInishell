/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brulutaj <brulutaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:50:03 by brulutaj          #+#    #+#             */
/*   Updated: 2024/07/16 10:10:38 by brulutaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *create_list_from_envp(char **envp)
{
	int rows = 0;

	t_list *node_set = NULL;
	t_list *env = NULL;
	while (envp && envp[rows])
	{
		node_set = ft_lstnew(ft_strdup(envp[rows]));
		ft_lstadd_back(&env, node_set);
		rows++;
	}
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_all	*token;

	while (1)
	{
		input = readline("Minishell~> ");
		if (!input)
			break ;
		printf("Input: %s\n", input);
		add_history(input);
		token = assign_tokens(input);
		free(input);
	}
	return (0);
}
