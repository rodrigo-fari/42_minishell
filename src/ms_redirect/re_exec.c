/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeberius <aeberius@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:22:54 by aeberius          #+#    #+#             */
/*   Updated: 2025/03/14 18:39:04 by aeberius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirects(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIR_OUT)
			redirect_output(tmp->next->value, 0);
		else if (tmp->type == TOKEN_REDIR_IN)
			redirect_input(tmp->next->value);
		else if (tmp->type == TOKEN_REDIR_OUT_APPEND)
			redirect_output(tmp->next->value, 1);
		else if (tmp->type == TOKEN_REDIR_ERR)
			redirect_error(tmp->next->value, 0);
		else if (tmp->type == TOKEN_REDIR_ERR_APPEND)
			redirect_error(tmp->next->value, 1);
		tmp = tmp->next;
	}
}
