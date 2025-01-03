/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:16:33 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/20 10:46:22 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	listadd_back(t_env **lst, t_env *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		list_last(*lst)->next = new;
}

t_env	*list_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	free_env_struct(t_env *env)
{
	t_env	*tmp;

	while (env->next)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		tmp = env->next;
		free(env);
		env = tmp;
	}
	if (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

int	listsize(t_env *env)
{
	size_t	size;

	if (env == NULL)
		return (0);
	size = 1;
	while (env->next != NULL)
	{
		size++;
		env = env->next;
	}
	return (size);
}
