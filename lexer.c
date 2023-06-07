/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:08:55 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/07 23:22:31 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_characters(char *str, char x)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str == NULL)
	{
		new_str = malloc(2);
		new_str[0] = x;
		new_str[1] = '\0';
	}
	else
	{
		new_str = malloc(ft_strlen(str) + 2);
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = x;
		new_str[i + 1] = '\0';
	}
	return (new_str);
}

char	*ft_norm(char *str, char x, int flag)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str == NULL)
		new_str = add_characters(str, x);
	else
	{
		new_str = malloc(ft_strlen(str) + 2);
		while (str[i++])
			new_str[i] = str[i];
		if (flag == 1)
		{
			new_str[i] = x;
			new_str[i + 1] = x;
			new_str[i + 2] = '\0';
		}
		else
		{
			new_str[i] = x;
			new_str[i] = '\0';
		}
	}
	return (new_str);
}

t_tokens	*ft_norm2(char *str, t_tokens *lexer, int type)
{
	t_tokens	*node;

	node = create_token(str, type);
	add_token(&lexer, node);
	return (lexer);
}

void	process_token(char *str, int type, t_tokens **lexer)
{
	t_tokens	*node;

	node = ft_norm2(str, *lexer, type);
	*lexer = node;
}

void	process_special_token(char *in, int *i, t_tokens **lexer)
{
	char	*str;

	if (in[*i] == '<')
	{
		if (in[*i + 1] == '<')
		{
			str = ft_norm(NULL, '<', 1);
			*i += 2;
			process_token(str, T_HERD, lexer);
		}
		else
		{
			str = ft_norm(NULL, '<', 0);
			(*i) += 1;
			process_token(str, T_IN_RD, lexer);
		}
	}
	else if (in[*i] == '>')
	{
		if (in[*i + 1] == '>')
		{
			str = ft_norm(NULL, '>', 1);
			*i += 2;
			process_token(str, T_APP, lexer);
		}
		else
		{
			str = ft_norm(NULL, '>', 0);
			(*i)++;
			process_token(str, T_OUT_RD, lexer);
		}
	}
	else if (in[*i] == '|')
	{
		str = ft_norm(NULL, '|', 0);
		(*i)++;
		process_token(str, T_PIPE, lexer);
	}
	else
	{
		str = ft_norm(NULL, in[*i], 0);
		(*i)++;
		process_token(str, T_STR, lexer);
	}
}

t_tokens	*lexer_init(char *in)
{
	int			i;
	char		*str;
	t_tokens	*lexer;

	lexer = NULL;
	i = 0;
	while (1)
	{
		if (in[i] == '\0' || in[i] == '\n')
			break ;
		while (in[i] != '\0')
		{
			if (in[i] == ' ' || in[i] == '\t')
				i++;
			str = NULL;
			if (ft_isalpha(in[i]) || in[i] == ' ' || in[i] == '\t'
				|| in[i] == '$' || in[i] == '.' || in[i] == '_')
			{
				while (in[i] && (ft_isalpha(in[i]) || in[i] == ' '
						|| in[i] == '\t' || in[i] == '$' || in[i] == '.'
						|| in[i] == '_'))
				{
					str = add_characters(str, in[i]);
					i++;
				}
				process_token(str, T_STR, &lexer);
			}
			else
				process_special_token(in, &i, &lexer);
		}
	}
	process_token(NULL, T_EOF, &lexer);
	return lexer;
}
