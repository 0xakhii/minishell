/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:07:29 by ojamal            #+#    #+#             */
/*   Updated: 2023/02/26 13:59:09 by ojamal           ###   ########.fr       */
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

#define D_QUOTE 34
#define S_QUOTE 39
#define B_SLASH 92
#define SPACE 32
#define TAB 9
#define PIPE 124
#define SEMICOLON 59
#define REDIR_IN 60
#define REDIR_OUT 62
#define APPEND 62


int	get_cmd();
int	check_all(char *input);
int	ft_isquote(char c);
int	ft_isredir(char c);
int	ft_ispipe(char c);


#endif