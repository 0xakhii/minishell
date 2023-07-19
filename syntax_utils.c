/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 04:40:53 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/18 18:54:56 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_quote(t_quote **stack, char quote)
{
	t_quote	*new_node;

	new_node = malloc(sizeof(t_quote));
	new_node->quote = quote;
	new_node->next = *stack;
	*stack = new_node;
}

int	msg_er(char *str)
{
	ft_putstr_fd("\033[1;31m[Minishell]\033[0m:", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	pop_quote(t_quote **stack)
{
	t_quote	*temp;

	if (*stack == NULL)
		return ;
	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}
