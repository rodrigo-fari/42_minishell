/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:01:47 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/15 16:20:57 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	char		*input;
	t_env		*env;
	extern char	**environ;
	char		*prompt;

	env = env_to_struct(environ);
	prompt = "\001\033[1;32m\002│42├Msh\001\033[0m\002: \001\033[1;35m\002";
	while (true)
	{
		input = readline(prompt);
		if (input)
		{
			add_history(input);
			ms_exec(env, input);
			free(input);
		}
	}
}

//* place above "input = readline" -> signal(SIGINT, sig_ctrl_c);