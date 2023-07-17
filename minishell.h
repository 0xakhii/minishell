/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:07:29 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/17 03:45:10 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <history.h>
# include <limits.h>
# include <readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
// # include "Leak_Hunter/leak_hunter.h"

typedef struct s_cmd
{
	char				**cmd;
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
	int					key_len;
	char				*value_start;
	char				*key;
	int					exit_status;
	int					flag;
}						t_helper;
t_helper				g_helper;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_herd
{
	char				*val;
	int					type;
	struct s_herd		*next;
}						t_herd;

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

char					*get_currdir(t_env_node *env);
char					*join_str(char *s1, char *s2);
void					free_tokens(t_tokens **t);
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
int						syntax_check(t_tokens *lexer);
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
t_env_node				*create_env_node(char *key, char *value);
t_tokens				*out_files(t_cmd **new_cmd, t_tokens *current_token,
							t_env_node *env);
t_tokens				*in_files(t_cmd **new_cmd, t_tokens *current_token,
							t_env_node *env);
void					create_herdoc(char *str, t_env_node *env, t_cmd *cmd);
char					*replace_value(char *str, t_env_node *env, int flag);
char					*get_dir(int flag, t_env_node *env);
char					expand_norm(char c, char *str, int i);
void					herd_sig(int sig);
void					herd_wait_sig(int pid, t_cmd *cmd, int pipefd[2]);

//------------------------------exec----------------//
void					echo_cmd(char **str);
void					set_env_value(t_env_node **env, const char *key,
							const char *value);
char					**node_to_2d(t_env_node *env);
void					print_env(char **cmd, t_env_node *env);
void					my_exit(t_cmd *cmd);
void					pwd_cmd(t_env_node *env);
int						cd_cmd(t_cmd *cmd, t_env_node **env);
void					execute_builtins(t_cmd *cmd, t_env_node **env);
int						is_builtins(t_cmd *cmd);
void					execute(t_cmd *cmd, t_env_node **env_list);
char					*ft_get_path(char *cmd, t_env_node *env);
void					my_unset(t_cmd *cmd, t_env_node **env);
void					export_variable(t_cmd *cmd, t_env_node **env);
void					ft_freeeeee(char **av);
void					ft_exec(t_cmd *cmd, t_env_node *env);
void					add_node(t_env_node **env, char *key, char *value);
t_env_node				*find_node(t_env_node **env, char *key);
int						get_exit_status(int status);
void					sig_handler(int sig);
void					ft_lunch(t_cmd *cmd, t_env_node *env_list);
void					print_export(t_env_node **env);
void					wait_and_signal(t_cmd *cmd);
#endif
