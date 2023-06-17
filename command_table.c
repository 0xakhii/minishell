/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/17 01:52:19 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*create_command_table(t_tokens *lexer)
// {
// 	t_cmd		*command_table;
// 	t_cmd		*current_cmd;
// 	char		**arguments;
// 	int			i;
// 	int			j;
// 	char		**new_arguments;
// 	t_tokens	*current_token;

// 	current_token = lexer;
// 	command_table = NULL;
// 	current_cmd = NULL;
// 	arguments = NULL;
// 	i = 0;
// 	while (lexer != NULL)
// 	{
// 		if (current_cmd == NULL)
// 		{
// 			command_table = (t_cmd *)malloc(sizeof(t_cmd));
// 			command_table->cmd = NULL;
// 			command_table->in_file = NULL;
// 			command_table->out_file = NULL;
// 			command_table->pipe = 0;
// 			current_cmd = command_table;
// 		}
// 		else if (current_token->e_types == T_STR)
// 		{
// 			while (current_token->e_types == T_STR)
// 			{
// 				i++;
// 				current_token = current_token->next;
// 			}
// 			j = 0;
// 			new_arguments = (char **)malloc((i + 2) * sizeof(char *));
// 			while (j < i)
// 			{
// 				new_arguments[j] = arguments[j];
// 				j++;
// 			}
// 			new_arguments[j] = ft_strdup(lexer->val);
// 			new_arguments[j + 1] = NULL;
// 			free(arguments);
// 			arguments = new_arguments;
// 			i++;
// 		}
// 		lexer = lexer->next;
// 	}
// 	if (current_cmd != NULL)
// 		current_cmd->cmd = arguments;
// 	return (command_table);
// }
