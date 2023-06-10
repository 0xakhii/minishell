/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/10 05:45:13 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_command_table(t_tokens *lexer)
{
	int cmd_count;
	t_cmd *cmd_table;
	t_tokens *current_token = lexer;

	cmd_count = 0;
	while (current_token)
	{
		if (current_token->e_types == 1)
			cmd_count++;
		current_token = current_token->next;
	}
	cmd_table = malloc(sizeof(t_cmd) * cmd_count);
}