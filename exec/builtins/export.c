/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:16:05 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/27 09:33:48 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_emptyy(char *cmd)
{
	int i;

	i = 0;
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
	int id = 0;

	if (str[0] == '+')
	{
		printf("export: not a valid identifier\n");
		return 0;
	}
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
		{
			if (id && str[i] != '+' && !(str[i] == '=' && str[i - 1] == '+'))
			{
				printf("export: not a valid identifier\n");
				return 0;
			}
			else if (!id)
				id = 1;
		}
		i++;
	}
	return 1;
}


void add_node(t_env_node **env, char *key, char *value)
{
	t_env_node *new_node;
	t_env_node *temp;

	temp = *env;
	new_node = create_env_node(key, value);
	if (*env == NULL)
		*env = new_node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_env_node *find_node(t_env_node **env, char *key)
{
	t_env_node *tmp = *env;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, key))
			return tmp;
		tmp = tmp->next;
	}
	return NULL; 
}

void	print_export(t_env_node **env)
{
	t_env_node *tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->key)
		{
			printf("declare -x %s", tmp->key);
			if (ft_strcmp(tmp->value, "\0"))
			{
				if (tmp->value[0] != '\"' && tmp->value[ft_strlen(tmp->value) - 1] != '\"')
					printf("=\"%s\"", tmp->value);
				else
					printf("=%s", tmp->value);
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}

void	append_to_export(char *key, char *value, t_env_node **env)
{
	t_env_node *existing;

	if (check_inputt(key))
	{
		existing = find_node(env, key);
		if (existing && value)
			existing->value = ft_strdup(value);
		else
			add_node(env, key, value);
	}
}

void export_variable(t_cmd *cmd, t_env_node **env)
{
	char **equal_sign;
	char *value;
	char *key;

	if (!cmd->cmd[1])	
		print_export(env);
	else
	{
		cmd->cmd++;
		while (*cmd->cmd)
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
