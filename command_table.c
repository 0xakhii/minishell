/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/18 00:50:43 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_command_table(t_tokens *lexer)
{
	t_cmd		*cmd_table = NULL;
	t_cmd *head = NULL;
	t_tokens	*current_token;
	cmd_table = ft_calloc(sizeof(t_cmd), 1);
	head = cmd_table;
	current_token = lexer;
	while (current_token)
	{
		if (current_token->e_types == T_STR)
		{
			cmd_table->cmd = ft_split(current_token->val, ' ');
			cmd_table->e_types = T_CMD;
			current_token = current_token->next;
		}
		else if (current_token->e_types == T_IN_RD
			|| current_token->e_types == T_HERD)
		{
			if (current_token->e_types == T_IN_RD)
			{
				current_token = current_token->next;
				cmd_table->in_file = ft_strdup(current_token->val);
				cmd_table->e_types = T_IN_FILE;
			}
			else
			{
				current_token = current_token->next;
				cmd_table->in_file = ft_strdup(current_token->val);
				cmd_table->e_types = T_HERD_FILE;
			}
		}
		else if (current_token->e_types == T_OUT_RD
			|| current_token->e_types == T_APP)
		{
			if (current_token->e_types == T_OUT_RD)
			{
				current_token = current_token->next;
				cmd_table->out_file = ft_strdup(current_token->val);
				cmd_table->e_types = T_OUT_FILE;
			}
			else
			{
				current_token = current_token->next;
				cmd_table->out_file = ft_strdup(current_token->val);
				cmd_table->e_types = T_APP_FILE;
			}
		}
		current_token = current_token->next;
	}
	return (head);
}
