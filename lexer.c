/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:24:23 by ojamal            #+#    #+#             */
/*   Updated: 2023/05/09 18:38:36 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*tokens(t_lex **lexer, char *str, int type)
{
	go_next(*lexer);
	return (initialize_token(str, type));
}

t_tokens	*others(t_lex *lexer)
{
	if (lexer->l == '|')
		return (tokens(&lexer, "|", T_PIPE));
	if (lexer->l == '<')
	{
		go_next(lexer);
		if (lexer->l == '<')
			return (tokens(&lexer, "<<", T_HERD));
		return (initialize_token("<", T_IN_RD));
	}
	if (lexer->l == '>')
	{
		go_next(lexer);
		if (lexer->l == '>')
			return (tokens(&lexer, ">>", T_APP));
		return (initialize_token(">", T_OUT_RD));
	}
	else
		return (initialize_token("newline", T_EOF));
}

t_tokens	*select_token(t_lex *lexer)
{
	t_tokens	*token;
	char	*str;
	char	c;

	str = NULL;
	while (lexer->l && (lexer->l == ' ' || lexer->l == '\t'))
		go_next(lexer);
	c = 0;
	while (lexer->l)
	{
		if ((lexer->l == '\"' || lexer->l == '\'') && c == 0)
			c = lexer->l;
		else if (c != 0 && lexer->l == c)
			c = 0;
		if ((lexer->l == '|' || lexer->l == '<' || lexer->l == '>'
				|| lexer->l == ' ') && c == 0)
			break ;
		str = add_str(str, lexer->l);
		go_next(lexer);
	}
	if (str)
		token = initialize_token(str, T_STR);
	else
		token = others(lexer);
	return (token);
}

t_list	*lexecal_analyzer(char *str)
{
	t_lex	lexer;
	t_tokens	*token;
	t_list	*list;

	if (!str)
		return (NULL);
	initialize_lexer(&lexer, str);
	list = NULL;
	while (lexer.l != '\0')
	{
		token = select_token(&lexer);
		ft_lstadd_back(&list, ft_lstnew(token));
	}
	token = initialize_token(NULL, T_EOF);
	ft_lstadd_back(&list, ft_lstnew(token));
	return (list);
}
t_tokens	*initialize_token(char *str, int type)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->e_token = type;
	token->val = str;
	return (token);
}
void	initialize_lexer(t_lex *lexer, char *str)
{
	lexer->fill = str;
	lexer->nxt = 0;
	lexer->l = lexer->fill[lexer->nxt];
}

void	go_next(t_lex *lexer)
{
	lexer->nxt++;
	lexer->l = lexer->fill[lexer->nxt];
}

t_tokens	*initialize_token(char *str, int type)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->e_token = type;
	token->val = str;
	return (token);
}
char	*add_str(char *str, char c)
{
	char *chr;
	char *save;

	chr = malloc(sizeof(char) * 2);
	chr[0] = c;
	chr[1] = '\0';
	if (!str)
	{
		str = chr;
		return (str);
	}
	else
	{
		save = str;
		str = ft_strjoin(str, chr);
		free(save);
		free(chr);
	}
	return (str);
}