/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 08:46:30 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/21 02:50:09 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_equal(const char *str1, const char *str2)
{
	size_t	size;

	if (!str1 || !str2)
		return (0);
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return (0);
	return (ft_strncmp(str1, str2, size) == 0);
}