/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:13:04 by ojamal            #+#    #+#             */
/*   Updated: 2023/07/20 22:41:02 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(t_env_node *env, char *str)
{
	char	*val;
	t_env_node *tmp;

	tmp = env;
	val = NULL;
	while (tmp)
	{
		if (tmp->key && tmp->value && str)
		{
			if (!ft_strcmp(tmp->key, str))
			{
				val = tmp->value;
				break ;
			}
		}
		tmp = tmp->next;
	}
	if (val == NULL)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*get_value(char *res, char *str, int *i, t_env_node *env)
{
	char	*id;
	char	*value;
	char	*val;

	id = NULL;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		val = ft_itoa(g_helper.exit_status);
		res = ft_strjoin(res, val);
		free(val);
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			id = add_characters(id, str[(*i)++]);
		value = get_env_val(env, id);
		res = ft_strjoin(res, value);
		free(id);
		free(value);
	}
	else
		res = add_characters(res, '$');
	return (res);
}

char	*replace_value(char *str, t_env_node *env, int flag)
{
	int		i;
	char	*res;
	char	c;

	i = 0;
	res = NULL;
	c = 0;
	if (flag == 0)
		return (str);
	while (str[i])
	{
		c = expand_norm(c, str, i);
		if ((flag != 2 || c != '\'') && str[i] == '$')
		{
			if (c == 0 && (str[i + 1] == '\"' || str[i + 1] == '\'')
				&& flag == 2)
				i++;
			else
				res = get_value(res, str, &i, env);
		}
		else
			res = add_characters(res, str[i++]);
	}
	return (res);
}

char	*split_var(char *str, int *i)
{
	char	*res;
	char	c;

	res = NULL;
	c = 0;
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\v')
		(*i)++;
	while (str[*i])
	{
		if (res == NULL)
			res = add_characters(res, '\0');
		if (c == 0 && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\v'))
			return (res);
		if (c == 0 && (str[*i] == '\'' || str[*i] == '\"'))
			c = str[*i];
		else if (str[*i] == c)
			c = 0;
		else
			res = add_characters(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	**new_expand(char *str, t_env_node *env, int flag)
{
	int		i;
	char	**split;
	char	**save;
	char	*tmp;
	char	*res;

	i = 0;
	split = NULL;
	save = NULL;
	res = replace_value(str, env, flag);
	while (res && res[i])
	{
		tmp = split_var(res, &i);
		if (!tmp)
			break ;
		save = split;
		split = ft_arrjoin(split, tmp);
		free(save);
		free(tmp);
	}
	free(res);
	return (split);
}
