/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/04 16:54:00 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

void	pwd_cmd(t_env_node *env)
{
	char *tmp;
	tmp = getcwd(0, 0);
	if (!tmp)
		printf("%s\n", get_env_val(env, "PWD"));
	else
		printf("%s\n", tmp);
	free(tmp);
}
