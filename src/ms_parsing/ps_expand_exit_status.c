/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expand_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:48:52 by rde-fari          #+#    #+#             */
/*   Updated: 2025/03/18 10:38:46 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_exit_status_in_command(char **command)
{
	char	*pos;

	pos = ft_strnstr(*command, "$?", ft_strlen(*command));
	while (pos)
	{
		replace_exit_status_at_pos(command, pos);
		pos = ft_strnstr(*command, "$?", ft_strlen(*command));
	}
}

void	replace_exit_status_at_pos(char **command, char *pos)
{
	char	*expanded_str;
	char	*remaining_str;
	char	*itoa_str;
	char	*temp;
	char	*substr;

	itoa_str = ft_itoa(g_exit_status);
	substr = ft_substr(*command, 0, pos - *command);
	expanded_str = ft_strjoin(substr, itoa_str);
	remaining_str = ft_strdup(pos + 2);
	temp = *command;
	*command = ft_strjoin(expanded_str, remaining_str);
	free(temp);
	free(expanded_str);
	free(remaining_str);
	free(itoa_str);
	free(substr);
}

void	replace_exit_status(char **commands, int i)
{
	replace_exit_status_in_command(&commands[i]);
}

void	expand_exit(char **commands)
{
	int		i;
	int		j;
	int		quotes;

	i = 0;
	while (commands[i])
	{
		quotes = 0;
		j = 0;
		while (commands[i][j])
		{
			if (commands[i][j] == '"')
				quotes = !quotes;
			if (!quotes)
				replace_exit_status(commands, i);
			j++;
		}
		i++;
	}
}
