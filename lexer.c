/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:08:55 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/15 00:46:19 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_token(char *str, int type, t_tokens **lexer)
{
	t_tokens	*node;

	node = ft_norm2(str, *lexer, type);
	*lexer = node;
}

void	process_redir1(char *in, char *str, int *i, t_tokens **lexer)
{
	if (in[*i] == '<')
	{
		if (in[*i + 1] == '<')
		{
			str = malloc(3);
			str[0] = '<';
			str[1] = '<';
			str[2] = '\0';
			*i += 2;
			process_token(str, T_HERD, lexer);
		}
		else
		{
			str = malloc(2);
			str[0] = '<';
			str[1] = '\0';
			(*i) += 1;
			process_token(str, T_IN_RD, lexer);
		}
	}
}

void	process_redir2(char *in, char *str, int *i, t_tokens **lexer)
{
	if (in[*i] == '>')
	{
		if (in[*i + 1] == '>')
		{
			str = malloc(3);
			str[0] = '>';
			str[1] = '>';
			str[2] = '\0';
			*i += 2;
			process_token(str, T_APP, lexer);
		}
		else
		{
			str = malloc(2);
			str[0] = '>';
			str[1] = '\0';
			(*i)++;
			process_token(str, T_OUT_RD, lexer);
		}
	}
}

void	process_special_token(char *in, char *str, int *i, t_tokens **lexer)
{
	process_redir1(in, str, i, lexer);
	process_redir2(in, str, i, lexer);
	if (in[*i] == '|')
	{
		str = malloc(2);
		str[0] = '|';
		str[1] = '\0';
		(*i)++;
		process_token(str, T_PIPE, lexer);
	}
	else
	{
		str = malloc(2);
		str[0] = in[*i];
		str[1] = '\0';
		(*i)++;
		process_token(str, T_STR, lexer);
	}
}

t_tokens	*lexer_init(char *in)
{
	t_tokens	*lexer;

	lexer = NULL;
	process_all(in, &lexer);
	process_token(NULL, T_EOF, &lexer);
	return (lexer);
}
