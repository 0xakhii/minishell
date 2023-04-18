/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:24:23 by ojamal            #+#    #+#             */
/*   Updated: 2023/04/18 03:08:56 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*lstlast(t_tokens *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst -> next;
	return (lst);
}


void	lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*ptr;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
	}
	else
	{
		ptr = lstlast(*lst);
		ptr -> next = new;
	}
}

void char_add(char c, t_tokens **head)
{
    if (!head)
    {
        head = malloc(sizeof(t_tokens));
    }
    if (!(*head))
    {
        (*head) = malloc(2);
        (*head)->val[0] = c;
        (*head)->val[1] = '\0';
    }
    else
        (*head)->val = ft_strjoin((*head)->val, &c);
}

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
    printf("-->\n");
	// if ((*head)->types == T_STR)
	// 	*head = (*head)->next;
	token = creat_tokens(val, type);
	if (!*head)
	{
		*head = token;
		return ;
	}
	// else
	// 	lstadd_back(head, token);
}

void get_tokens(char *input)
{
    int i;
    t_tokens *head;

    head = NULL;
    i = 0;
    while (input[i])
    {
        if (input[i] == '|')
            add_tokens(&head, "|", T_PIPE);
        else if (input[i] == '<' && input[i + 1] == '<')
            add_tokens(&head, "<<", T_HERD);
        else if (input[i] == '>' && input[i + 1] == '>')
            add_tokens(&head, ">>", T_APP);
        else if (input[i] == '>')
            add_tokens(&head, ">", T_OUT_RD);
        else if (input[i] == '<')
            add_tokens(&head, "<", T_IN_RD);
        else
            char_add(input[i], &head);
        i++;
    }
    // if (input[i] == '\0')
    //     add_tokens(&head, &input[i], T_OEF);
    while (head)
    {
        printf("%d\n", (head)->types);
        head = (head)->next;
    }
}