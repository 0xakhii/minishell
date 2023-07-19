/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:32:43 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/18 18:54:40 by ojamal           ###   ########.fr       */
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
		free(str);
	}
	return (new_str);
}

int	ft_isspecial(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	process_alnum(char *in, char *str, int *i, t_tokens **lexer)
{
	char	c;

	c = 0;
	while (in[*i])
	{
		if (c == 0 && (in[*i] == '\'' || in[*i] == '\"'))
			c = in[*i];
		else if (in[*i] == c)
			c = 0;
		if (c == 0 && (ft_isspecial(in[*i]) || in[*i] == ' ' || in[*i] == '\t'
				|| in[*i] == '\v'))
			break ;
		str = add_characters(str, in[*i]);
		(*i)++;
	}
	if (str)
		process_token(str, T_STR, lexer);
	return (str == NULL);
}

void	process_all(char *in, t_tokens **lexer)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		while (in[i] == ' ' || in[i] == '\t' || in[i] == '\v')
			i++;
		if (in[i] == '\0' || in[i] == '\n')
			break ;
		str = NULL;
		if (process_alnum(in, str, &i, lexer))
			process_special_token(in, str, &i, lexer);
	}
}

t_tokens	*ft_norm2(char *str, t_tokens *lexer, int type)
{
	t_tokens	*node;

	node = create_token(str, type);
	add_token(&lexer, node);
	return (lexer);
}
