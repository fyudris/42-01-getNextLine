/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:17:18 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/07 16:08:23 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

/**
 * @brief Appends buffer contents to line
 */
char	*ft_strjoin_gnl(char *line, char *buffer, int *eol_post)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!line || !buffer)
		return (NULL);

	len1 = ft_strlen(line);
	len2 = ft_strlen(buffer);
	result = (char *) malloc (sizeof(char) * (len1 + len2 + 1));
	if (!result)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy(result, line, len1);
	free(line);
	ft_memcpy(result + len1, buffer, len2 + 1);
	if (len1 + len2 > 0 && *(result + len1 + len2 - 1) == '\n')
		*eol_post = 0;
	return (result);
}

/**
 * @brief Saves leftover data in stash
 */
void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}
