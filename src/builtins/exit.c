/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:17:57 by chsassi           #+#    #+#             */
/*   Updated: 2024/07/30 10:19:00 by chsassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_exit(char **input/* t_all *pAll */)
{
	if (!ft_strcmp(*input, "exit"))
	{
		write(1, "exit\n", 5);
		free(/*free struct*/NULL);
		exit(0);
	}
}

// da leggere il funzionamento di exit con le pipe
// da leggere il funzionamento degli exit status