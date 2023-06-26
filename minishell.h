/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:07:29 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/26 01:32:08 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char				**cmd;
	char				*in_file;
	char				*out_file;
	int					pipe;
	int					in_fd;
	int					out_fd;
	int					fd[2];
	int					pid;
	enum
	{
		T_CMD,
		T_HERD_FILE
	} e_types;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_quote
{
	char				quote;
	struct s_quote		*next;
}						t_quote;

typedef struct s_helper
{
	int					i;
	char				*equal_sign;
	size_t				key_len;
	char				*value_start;
	char				*key;
	int					exit_status;
}						t_helper;
// t_helper g_helper;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
	int					i;
}						t_env_node;

typedef struct s_tokens
{
	char				*val;
	enum
	{
		T_PIPE,
		T_STR,
		T_IN_RD,
		T_OUT_RD,
		T_HERD,
		T_APP,
		T_EOF
	} e_types;
	struct s_tokens		*next;
}						t_tokens;

void					printing(t_tokens *lexer);
void					ft_free(char **str);
void					execute_first_command(t_cmd *cmd, char **env,
							t_env_node *env_node);
void					push_quote(t_quote **stack, char quote);
void					pop_quote(t_quote **stack);
char					*add_characters(char *str, char x);
int						ft_isspecial(char c);
t_tokens				*ft_norm2(char *str, t_tokens *lexer, int type);
void					process_all(char *in, t_tokens **lexer);
void					process_special_token(char *in, char *str, int *i,
							t_tokens **lexer);
void					process_token(char *str, int type, t_tokens **lexer);
t_tokens				*lexer_init(char *in);
int						msg_er(char *str);
void					printing2(t_env_node *lexer);
int						syntax_check(t_tokens *lexer);
int						get_cmd(void);
t_tokens				*expand_command(t_tokens *lexer, t_env_node *env_list);
t_env_node				*create_env_list(char **env);
void					get_tokens(char *input);
int						token_check(t_tokens *lexer);
char					*get_prompt(void);
int						open_files(t_cmd *cmd);
t_tokens				*create_token(char *val, int type);
void					add_token(t_tokens **lexer, t_tokens *node);
t_cmd					*create_command_table(t_tokens *lexer, t_env_node *env);
char					*get_env_val(t_env_node *env, char *str);
char					**new_expand(char *str, t_env_node *env, int flag);
char					**ft_arrjoin(char **split, char *str);

//------------------------------exec----------------//
void					echo_cmd(char **str);
void					print_env(char **cmd, t_env_node *env);
void					my_exit(t_cmd *cmd);
void					pwd_cmd(void);
int						cd_cmd(t_cmd *cmd, t_env_node **env, char *curpwd);
void					execute_builtins(t_cmd *cmd, t_env_node **env);
int						is_builtins(t_cmd *cmd);
void					execute(t_cmd *cmd, t_env_node **env_list, char **env);
char					*ft_get_path(char *cmd, t_env_node *env);
void					my_unset(t_cmd *cmd, t_env_node **env);
void					export_variable(t_cmd *cmd, t_env_node **env);
void					ft_freeeeee(char **av);
void					ft_exec(t_cmd *cmd, t_env_node *env);
#endif
