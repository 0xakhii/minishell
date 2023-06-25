/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:05 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/24 08:26:17 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_emptyy(char *cmd)
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

int	check_inputt(char *str)
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
	return (1);
}

void add_node(t_env_node **env, char *key, char *value)
{
	t_env_node *new_node = (t_env_node *)malloc(sizeof(t_env_node));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value); 
	new_node->next = NULL;

	// If the env list is empty, make the new node the head
	if (*env == NULL)
		*env = new_node;
	else
	{
		// Find the last node and add the new node to the end
		t_env_node *temp = *env;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
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
	char **args = cmd->cmd;
	tmp = *env;
	if (!cmd->cmd[1])
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
			char **equal_sign = ft_split(*args, '=');
			if (equal_sign[0])
				key = equal_sign[0];
			if (!equal_sign[1] && ft_strchr(*args, '='))
				value = "\"\"";
			else if (equal_sign[1] == 0)
				value = "\0";
			else
				value = equal_sign[1];
			add_node(env, key, value);
			printf("Exported variable: %s=%s\n", key, value);
			args++;
		}
	}
}

