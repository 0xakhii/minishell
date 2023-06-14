/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/14 17:50:21 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd* create_command_table(t_tokens* lexer) {
    t_cmd* command_table = NULL;
    t_cmd* current_cmd = NULL;
    int arg_count = 0;
    int arg_capacity = 2;
    char** arguments = (char**)malloc(arg_capacity * sizeof(char*));

    while (lexer != NULL) {
        if (current_cmd == NULL) {
            command_table = (t_cmd*)malloc(sizeof(t_cmd));
            command_table->cmd = NULL;
            command_table->in_file = NULL;
            command_table->out_file = NULL;
            command_table->pipe = 0;
            current_cmd = command_table;
        }

        if (lexer->e_types == T_PIPE) {
            current_cmd->cmd = (char**)malloc((arg_count + 1) * sizeof(char*));
            int i = 0;
            while (i < arg_count) {
                current_cmd->cmd[i] = arguments[i];
                i++;
            }
            current_cmd->cmd[arg_count] = NULL;

            current_cmd->pipe = 1;
            current_cmd = NULL;
            arg_count = 0;
        } else if (lexer->e_types == T_STR) {
            if (arg_count + 1 >= arg_capacity) {
                arg_capacity *= 2;
                char** new_arguments = (char**)malloc(arg_capacity * sizeof(char*));
                int i = 0;
                while (i < arg_count) {
                    new_arguments[i] = arguments[i];
                    i++;
                }
                free(arguments);
                arguments = new_arguments;
            }

            arguments[arg_count] = strdup(lexer->val);
            arg_count++;
        } else if (lexer->e_types == T_IN_RD) {
            lexer = lexer->next;
            if (lexer != NULL && lexer->e_types == T_STR) {
                current_cmd->in_file = strdup(lexer->val);
            }
        } else if (lexer->e_types == T_OUT_RD || lexer->e_types == T_APP) {
            lexer = lexer->next;
            if (lexer != NULL && lexer->e_types == T_STR) {
                current_cmd->out_file = strdup(lexer->val);
            }
        }

        lexer = lexer->next;
    }

    if (current_cmd != NULL) {
        current_cmd->cmd = (char**)malloc((arg_count + 1) * sizeof(char*));
        int i = 0;
        while (i < arg_count) {
            current_cmd->cmd[i] = arguments[i];
            i++;
        }
        current_cmd->cmd[arg_count] = NULL;
    }

    free(arguments);

    return command_table;
}
