/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:13:04 by ojamal            #+#    #+#             */
/*   Updated: 2023/06/22 16:11:38 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(t_env_node *env, char *str)
{
	char	*val;

	val = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			val = env->value;
		env = env->next;
	}
	if (val == NULL)
		val = "";
	return (ft_strdup(val));
}

char	*get_value(char *res, char *str, int *i, t_env_node *env)
{
	char	*id;

	id = NULL;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		res = ft_strjoin(res, ft_itoa(g_helper.exit_status));
	}
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			id = add_characters(id, str[(*i)++]);
		id = get_env_val(env, id);
		res = ft_strjoin(res, id);
		free(id);
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
		if (c == 0 && (str[i] == '\"' || str[i] == '\''))
			c = str[i];
		else if (c == str[i])
			c = 0;
		if (c != '\'' && str[i] == '$')
			res = get_value(res, str, &i, env);
		else
			res = add_characters(res, str[i++]);
	}
	if (flag == 1)
		free(str);
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

void	my_free(char **str)
{
	int i = 0;
	while(str && str[i])
		free(str[i++]);
	free(str);
}

char	**new_expand(char *str, t_env_node *env)
{
	int i = 0;
	char **split = NULL;
	char **save = NULL;
	char *tmp;
	char *res = replace_value(str, env, 2);
	while (res[i])
	{
		tmp = split_var(res, &i);
		if (!tmp)
			break;
		save = split;
		split = ft_arrjoin(split, tmp);
		free(save);
		free(tmp);
	}
	return (split);
}