/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:19:21 by rde-fari          #+#    #+#             */
/*   Updated: 2024/12/10 12:24:21 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//=====================================| Colors |
# define RED    "\033[31m"
# define GREEN  "\033[32m"
# define ORANGE "\033[38;5;208m"
# define PURPLE "\e[35m"
# define YELLOW "\033[33m"
# define CYAN   "\033[36m"
# define RESET  "\033[0m"

//=====================================| Libraries |
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include "../src/ms_libft/libft/libft.h"

//#include "../../inc/minishell.h"
//Para a criacao dos arquivos

//=====================================| Support Defines |
//[clear.c]
# define CLEAR_CODE "\033[2J\033[H"

//=====================================| Structs |
typedef enum e_token_type
{
	TOKEN_WORD,// For commands and arguments
	TOKEN_PIPE,// For '|'
	TOKEN_REDIR_IN,// For '<'
	TOKEN_REDIR_OUT,// For '>'
	TOKEN_REDIR_APPEND,// For '>>'
	TOKEN_REDIR_HEREDOC,// For '<<'
	TOKEN_ENV_VAR,// For environment variables
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				value;
	struct s_token		*next;
}	t_token;

typedef struct s_command
{
	char				*command;
}	t_command;

typedef struct s_ast_node
{
	t_token_type		*type;
	char				args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

//=====================================| ms_built-in |
//[bi_echo.c]
void	bi_echo(char **args);
//[bi_cd.c]
void	bi_cd(void);
//[bi_exit.c]
void	bi_exit(void);
//[bi_export.c]
void	bi_export(void);
//[bi_pwd.c]
void	bi_pwd(void);
//[bi_unset.c]
void	bi_unset(void);
//[bi_error.c]
void	bi_error(char *str);
//[bi_commands.c]
void	exec_builtins(char **user_input, t_env *env);
void	exec_exe(char *command, char **user_input, t_env *env);

//=====================================| ms_env |
//[ev_env_to_struct.c]
t_env	*env_to_struct(char **environ);
//[ev_utils.c]
void	print_env(t_env *head);
t_env	*list_last(t_env *lst);
void	free_env_struct(t_env *env);
void	listadd_back(t_env **lst, t_env *new);

//=====================================| ms_extra |
//[ex_clear.c] LEMBRAR DE REMOVER ESTA FUNÇÃO! CLEAR TEM QUE BUSCAR O COMANDO NO ABSOLUTE E RELATIVE PATH! (NAO EXISTE NO MAC).
void	ex_clear(void);

//=====================================| ms_main |
//[ms_exec.c]
void	ms_exec(t_env *env, char *input);

//=====================================| ms_parsing |
//[ps_error.c]
void	ps_error(char *str, char **user_input);
//[ps_parsing.c]
bool	parsing(char *input);
//[ps_syntax.c]
bool	parse_pipes(char **user_input);
bool	parse_redin(char **user_input);
bool	parse_redout(char **user_input);
bool	parse_heredoc(char **user_input);
bool	parse_quotes(char *input, int i, int s_quote, int d_quote);

//=====================================| Endif |
#endif