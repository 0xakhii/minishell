/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 01:15:54 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/20 01:37:12 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_cmd(void)
{
	char *tmp;
	//Get path name of the working directory
	tmp = getcwd(0, 0); //success;
	if (!tmp)
		return ;
	else
		printf("%s\n", tmp);
	free(tmp);
}
