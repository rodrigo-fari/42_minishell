/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:34:15 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/18 11:37:51 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_expand(char *input)
{
	t_env	*tmp;

	tmp = env_manager(NULL);
	while (tmp)
	{
		if (ft_strcmp(input, tmp->key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
