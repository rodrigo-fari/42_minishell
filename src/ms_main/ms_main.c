/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:47:50 by rde-fari          #+#    #+#             */
/*   Updated: 2025/02/24 17:14:47 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(void)
{
	t_env		*env;
	char		*input;
	extern char	**environ;

	env = env_to_struct(environ);
	env = env_manager(env);
	while (true)
	{
		env = env_manager(NULL);
		input = readline("👹$ ");
		// signal(SIGINT, sig_ctrl_c);
		if (input[0])
		{
			add_history(input);
			env = env_manager(NULL);
			ms_exec(input, env);
		}
	}
	return (0);
}
