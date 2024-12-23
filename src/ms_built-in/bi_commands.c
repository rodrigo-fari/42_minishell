/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:18:50 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/19 14:41:40 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_builtins(char **user_input, t_env *env, char *input)
{
	env = env_manager(0);
	if (ft_strcmp(user_input[0], "echo") == 0)
		bi_echo(user_input);
	else if (ft_strcmp(user_input[0], "pwd") == 0)
		bi_pwd();
	else if (ft_strcmp(user_input[0], "clear") == 0)
		ex_clear();
	else if (ft_strcmp(user_input[0], "celar") == 0)
		ex_clear();
	else if (ft_strcmp(user_input[0], "exit") == 0)
		bi_exit(user_input, env, input);
	else if (ft_strcmp(user_input[0], "env") == 0)
		print_env(env);
	else if (ft_strcmp(user_input[0], "cd") == 0)
		bi_cd(user_input, env);
	else if (ft_strcmp(user_input[0], "unset") == 0)
		bi_unset(user_input, env);
	else if (ft_strcmp(user_input[0], "export") == 0)
		bi_export(env, user_input);
	else
	{
		free(input);
		exec_exe(user_input[0], user_input, env);
	}
}

void	exec_exe(char *command, char **user_input, t_env *env)
{
	char	*full_command;
	pid_t	execve_new_process;
	int		status;

	execve_new_process = fork();
	if (execve_new_process == 0)
	{
		if (ft_strchr(command, '/'))
		{
			printf("execve \n");
			execve(command, user_input, NULL);
		}
		else
		{
			full_command = ft_strjoin("/bin/", command);
			execve(full_command, user_input, NULL);
			printf("execve /bin/\n");
			free(full_command);
		}
		perror("execve");
		bi_exit(user_input, env, NULL);
	}
	else if (execve_new_process > 0)
		waitpid(execve_new_process, &status, 0);
	else
		perror("fork");
	(void)env;
}
