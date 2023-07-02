/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:05 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/07/02 21:06:47 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_emptyy(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int check_inputt(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') 
		|| str[i] == '_') || !check_emptyy(str))
		{
			printf("export: not a valid identifier\n");
			return (0);
		}
		i++;
	}
	return 1;
}

void add_node(t_env_node **env, char *key, char *value)
{
	t_env_node	*tmp;
	t_env_node *new_node;
	t_env_node *temp;

	// If the env list is empty, make the new node the head
	if (*env == NULL)
		*env = new_node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_env_node	*create_export_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}
void export_variable(t_cmd *cmd, t_env_node **env)
{
	t_env_node *tmp;

	tmp = *env;
	while (tmp)
	{
		while (tmp)
		{
			// printf("check\n");
			if (tmp->key)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->key, 1);
				if (ft_strcmp(tmp->value, "\0"))
					ft_putchar_fd('=', 1);
				// if (!ft_strcmp(tmp->value, "\\"))
				// {
				// 	ft_putstr_fd("\"\"\n", 1);
				// 	return ;
				// }
				ft_putstr_fd(tmp->value, 1);
				ft_putchar_fd('\n', 1);
			}
			tmp = tmp->next;
		}
	}
	if (cmd->cmd[1])
	{
		(*env)->i = 0;
		args++;
		char *value;
		char *key;
		while (*args)
		{
			value = NULL;
			equal_sign = ft_split(*cmd->cmd, '=');
			if (equal_sign[0])
				key = equal_sign[0];
			if (equal_sign[1] == NULL && ft_strchr(*cmd->cmd, '='))
				value = "\"\"";
			else if (equal_sign[1] == NULL)
				value = "\0";
			else
				value = equal_sign[1];
			append_to_export(key, value, env);
			cmd->cmd++;
		}
	}
}
