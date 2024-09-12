/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brulutaj <brulutaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:53:05 by brulutaj          #+#    #+#             */
/*   Updated: 2024/09/12 17:06:26 by brulutaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*find_env_string(char *input, t_env *envp, int len)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(*input, tmp->var, len))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*env_string(char *input, int *i)
{
	int	j;
	int	len;

	j = i;
	len = 0;
    *i++;
    if (input[*i] != '\0')
    {
		if (input[*i] == '?')
			return (ft_itoa(g_exit));
		else if (input[*i] == '_' || ft_isalpha(input[*i]))
		{
			(*i)++;
			while (input[*i] == '_' || ft_isalnum(input[*i]))
			    (*i)++;
			len = (*i) - j;
			return (ft_substr(input, input + 1, len));
		}
    }
	return (NULL);
}
