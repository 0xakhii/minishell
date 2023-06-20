/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/20 06:06:15 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*table_init(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->next = NULL;
	new_cmd->cmd = NULL;
	new_cmd->in_file = NULL;
	new_cmd->out_file = NULL;
	new_cmd->pipe = 0;
	return (new_cmd);
}

void	files_process(t_cmd **new_cmd, t_tokens *current_token)
{
	if (current_token->e_types == T_IN_RD || current_token->e_types == T_HERD)
	{
		if (current_token->next)
		{
			current_token = current_token->next;
			(*new_cmd)->in_file = ft_strdup(current_token->val);
			(*new_cmd)->e_types = T_IN_FILE;
		}
	}
	else if (current_token->e_types == T_OUT_RD
		|| current_token->e_types == T_APP)
	{
		if (current_token->next)
		{
			current_token = current_token->next;
			(*new_cmd)->out_file = ft_strdup(current_token->val);
			(*new_cmd)->e_types = T_OUT_FILE;
		}
	}
	else if (current_token->e_types == T_PIPE)
		(*new_cmd)->pipe = 1;
}

void	get_table(t_cmd **current_cmd, t_cmd **cmd_table, t_cmd *new_cmd)
{
	if (!*cmd_table)
	{
		*cmd_table = new_cmd;
		*current_cmd = *cmd_table;
	}
	else
	{
		(*current_cmd)->next = new_cmd;
		(*current_cmd) = (*current_cmd)->next;
	}
}


char **ft_arrjoin(char **ptr, char *s)
{
	ptr[0] = ft_strdup(s);
	ptr[1] = NULL;
	return ptr;	
}



t_cmd	*create_command_table(t_tokens *lexer)
{
	t_cmd		*cmd_table;
	t_cmd		*current_cmd;
	t_tokens	*current_token;
	t_cmd		*new_cmd;

	cmd_table = NULL;
	current_cmd = NULL;
	current_token = lexer;
	while (current_token)
	{
		new_cmd = table_init();
		if (current_token->e_types == T_STR)
		{
			new_cmd->cmd = ft_split(current_token->val, ' ');
			new_cmd->e_types = T_CMD;
		}
		files_process(&new_cmd, current_token);
		get_table(&current_cmd, &cmd_table, new_cmd);
		current_token = current_token->next;
	}
	return (cmd_table);
}
