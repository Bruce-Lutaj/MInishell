#include "minishell.h"

void	builtin_env(t_all *pAll)
{
	t_list	*tmp;

	tmp = pAll->envp;
	while (tmp)
	{
		ft_printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}