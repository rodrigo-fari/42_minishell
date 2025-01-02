/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:45:28 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/26 17:19:32 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_pipes(char **commands)
{
	int	i;
	i = 0;
	while (commands[i])
	{
		if (quote_verifier(commands[i]) && commands[i + 1])
			i++;
		if (commands[i][0] == '|')
		{
			if (!commands[i + 1] || !commands[i - 1])
			{
				ps_error("bash: syntax error near unexpected token: |");
				return (false);
			}
		}
		i++;
	}
	return (true);
}