/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_var_expand_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:27:20 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/14 15:30:52 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(char *str)
{
	char	*result;
	char	*start;
	char	*end;
	char	*var_value;
		
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	start = str;
	while ((end = ft_strchr(start, '$')))
	{
		result = process_segment(result, &start, end);
		var_value = replace_variable(start, &start);
		if (var_value)
		{
			result = append_str(result, var_value);
			free(var_value);
		}
	}
	return (append_str(result, start));
}

void	replace_env_variables(char **commands)
{
	int	 i;
	char	*result;

	i = 0;
	while (commands[i])
	{
		result = expand_variables(commands[i]);
		free(commands[i]);
		commands[i] = result;
		i++;
	}
}
