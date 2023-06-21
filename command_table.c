/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:28:27 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/21 11:22:27 by ojamal           ###   ########.fr       */
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
			if (current_token->e_types == T_IN_RD)
			{	
			current_token = current_token->next;
			(*new_cmd)->in_file = ft_strdup(current_token->val);
			(*new_cmd)->e_types = T_IN_FILE;
			}
			else
			{	
			current_token = current_token->next;
			(*new_cmd)->in_file = ft_strdup(current_token->val);
			(*new_cmd)->e_types = T_HERD_FILE;
			}
		}
	}
	else if (current_token->e_types == T_OUT_RD
			|| current_token->e_types == T_APP)
	{
		if (current_token->next)
		{
			if (current_token->e_types == T_OUT_RD)
			{	
			current_token = current_token->next;
			(*new_cmd)->in_file = ft_strdup(current_token->val);
			(*new_cmd)->e_types = T_OUT_FILE;
			}
			else
			{	
			current_token = current_token->next;
			(*new_cmd)->in_file = ft_strdup(current_token->val);
			(*new_cmd)->e_types = T_APP_FILE;
			}
		}
	}
	else if (current_token->e_types == T_PIPE)
	{
		(*new_cmd)->pipe++;
		(*new_cmd)->next = table_init();
		(*new_cmd) = (*new_cmd)->next;
	}
}

char	**ft_arrjoin(char **split, char *str)
{
	char	**new_split;
	int		i;

	i = 0;
	if (split == NULL)
	{
		new_split = malloc(2 * sizeof(char *));
		new_split[0] = ft_strdup(str);
		new_split[1] = NULL;
	}
	else
	{
		while (split[i])
			i++;
		new_split = malloc((i + 2) * sizeof(char *));
		i = 0;
		while (split[i])
		{
			new_split[i] = ft_strdup(split[i]);
			i++;
		}
		new_split[i] = ft_strdup(str);
		new_split[i + 1] = NULL;
	}
	return (new_split);
}

void	cmd_process(t_tokens *current_token, t_cmd **new_cmd, t_env_node *env)
{
		if (current_token->e_types == T_STR)
{
	
	int i = 0;
	char **str = new_expand(current_token->val, env);
	while (str && str[i])
	{
		(*new_cmd)->cmd = ft_arrjoin((*new_cmd)->cmd, str[i]);
		free(str[i++]);
	}
	free(str);
	(*new_cmd)->e_types = T_CMD;
}
}

t_cmd	*create_command_table(t_tokens *lexer, t_env_node *env)
{
	t_cmd		*cmd_table;
	t_tokens	*current_token;
	t_cmd		*new_cmd;

	cmd_table = NULL;
	current_token = lexer;
	new_cmd = table_init();
	cmd_table = new_cmd;
	while (current_token)
	{
		cmd_process(current_token, &new_cmd, env);
		files_process(&new_cmd, current_token);
		current_token = current_token->next;
	}
	return (cmd_table);
}
