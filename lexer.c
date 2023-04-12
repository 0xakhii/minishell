/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:24:23 by ojamal            #+#    #+#             */
/*   Updated: 2023/04/12 22:00:01 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens *creat_tokens(char *val, int type)
{
	t_tokens *tokens;

	tokens = malloc(sizeof(t_tokens));
	tokens->val = ft_strdup(val);
	tokens->types = type;
	tokens->next = NULL;
	return (tokens);
}

void	add_tokens(t_tokens **head, char *val, int type)
{
	t_tokens *token;
	t_tokens *tmp;

	token = creat_tokens(val, type);
	if (!*head)
	{
		*head = token;
		return ;
	}
	tmp = *head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

void	get_tokens(char *input)
{
	int	i;
	t_tokens *head;

	i = 0;
	head = NULL;
	while(input[i])
	{
		if (input[i] == '|')
			add_tokens(&head, input, T_PIPE);
		else if (input[i] == '>')
			add_tokens(&head, input, T_IN_RD);
		else if (input[i] == '<')
			add_tokens(&head, input, T_OUT_RD);
		else if ((input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
			add_tokens(&head, input, T_APP);
		else
			add_tokens(&head, input, T_STR);
		i++;
	}
	if (input[i] == '\0')
		add_tokens(&head, input, T_OEF);
	t_tokens *current = head;
    while (current != NULL)
    {
        printf("%s\n", current->val);
        current = current->next;
    }
}