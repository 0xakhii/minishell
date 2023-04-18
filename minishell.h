/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:07:29 by ojamal            #+#    #+#             */
/*   Updated: 2023/04/16 00:08:04 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct cmd
{
	char	*cmd;
	char	**args;
}				t_cmd;

typedef struct node
{
	t_cmd	*cmd;
	struct node	*next;   
}				t_node;

typedef struct s_tokens
{
	char *val;
	enum
	{
		T_PIPE,
		T_STR,
		T_IN_RD,
		T_OUT_RD,
		T_HERD,
		T_APP,
		T_OEF
	} types;
	struct s_tokens *next;
}	t_tokens;


int		get_cmd();
int		check_quote(char *input);
int		ft_isquote(char c);
int		ft_isredir(char c);
int		ft_ispipe(char c);
int		ft_isand(char c);
void	get_tokens(char *input);
char	*get_prompt();
t_tokens *creat_tokens(char *val, int type);

#endif