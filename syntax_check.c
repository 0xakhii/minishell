/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:17:20 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/16 00:23:05 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_start(t_tokens *lexer)
{
	if (lexer->e_types != 1)
	{
		if (lexer->e_types == 0)
			return (msg_er("syntax error near unexpected token `|'"));
		if (lexer->e_types == 2 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		if (lexer->e_types == 3 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		if (lexer->e_types == 4 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		if (lexer->e_types == 5 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
	}
	return (0);
}

int	token_check(t_tokens *lexer)
{
	if (check_start(lexer))
		return (1);
	while (lexer)
	{
		if (lexer->e_types == 0 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `|'"));
		if (lexer->e_types == 2 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		if (lexer->e_types == 3 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		if (lexer->e_types == 4 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		if (lexer->e_types == 5 && lexer->next && lexer->next->e_types != 1)
			return (msg_er("syntax error near unexpected token `newline'"));
		lexer = lexer->next;
	}
	return (0);
}

void	process_character(char c, t_quote **stack_double,
		t_quote **stack_single)
{
	if (c == '\"')
	{
		if (*stack_single == NULL || (*stack_single)->quote != '\'')
		{
			if (*stack_double == NULL || (*stack_double)->quote == '\'')
				push_quote(stack_double, '\"');
			else
				pop_quote(stack_double);
		}
	}
	else if (c == '\'')
	{
		if (*stack_double == NULL || (*stack_double)->quote != '\"')
		{
			if (*stack_single == NULL || (*stack_single)->quote == '\"')
				push_quote(stack_single, '\'');
			else
				pop_quote(stack_single);
		}
	}
}

void	process_string(char *str, t_quote **stack_double,
		t_quote **stack_single)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		process_character(str[i], stack_double, stack_single);
		i++;
	}
}

int	syntax_check(t_tokens *lexer)
{
	t_quote	*stack_single;
	t_quote	*stack_double;
	char	*str;

	stack_single = NULL;
	stack_double = NULL;
	while (lexer)
	{
		str = (char *)lexer->val;
		if (str != NULL)
			process_string(str, &stack_double, &stack_single);
		lexer = lexer->next;
	}
	if (stack_single != NULL)
		return (msg_er("Unclosed single quote: '\n"));
	if (stack_double != NULL)
		return (msg_er("Unclosed double quote: \"\n"));
	return (0);
}
