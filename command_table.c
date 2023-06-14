/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/14 17:34:38 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmd	*create_command_table(t_tokens *lexer)
{
	t_cmd *cmd_table = NULL;
	t_tokens *current_token = lexer;
	while(current_token)
	{
		if (cmd_table == NULL)
		{
			cmd_table = malloc(sizeof(t_cmd));
			if (current_token->e_types == T_STR)
				cmd_table->cmd[0] = current_token->val;
			cmd_table->cmd[1] = NULL;
			cmd_table->in_file = NULL;
			cmd_table->out_file = NULL;
		}
		current_token = current_token->next;
	}
	return cmd_table;
}