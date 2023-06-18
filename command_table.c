/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/18 06:24:07 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_command_table(t_tokens *lexer)
{
    t_cmd *cmd_table = NULL;
    t_cmd *current_cmd = NULL;
    t_tokens *current_token = lexer;

    while (current_token)
    {
        t_cmd *new_cmd = malloc(sizeof(t_cmd));
        new_cmd->next = NULL;
        new_cmd->cmd = NULL;
        new_cmd->in_file = NULL;
        new_cmd->out_file = NULL;
        new_cmd->pipe = 0;

        if (current_token->e_types == T_STR)
        {
            new_cmd->cmd = ft_split(current_token->val, ' ');
            new_cmd->e_types = T_CMD;
        }
        else if (current_token->e_types == T_IN_RD || current_token->e_types == T_HERD)
        {
            if (current_token->next)
            {
                current_token = current_token->next;
                new_cmd->in_file = ft_strdup(current_token->val);
                new_cmd->e_types = T_IN_FILE;
            }
        }
        else if (current_token->e_types == T_OUT_RD || current_token->e_types == T_APP)
        {
            if (current_token->next)
            {
                current_token = current_token->next;
                new_cmd->out_file = ft_strdup(current_token->val);
                new_cmd->e_types = T_OUT_FILE;
            }
        }
        else if (current_token->e_types == T_PIPE)
            new_cmd->pipe = 1;

        if (!cmd_table)
        {
            cmd_table = new_cmd;
            current_cmd = cmd_table;
        }
        else
        {
            current_cmd->next = new_cmd;
            current_cmd = current_cmd->next;
        }

        current_token = current_token->next;
    }
    return cmd_table;
}

