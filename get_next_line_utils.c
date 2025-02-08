/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:17:18 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/08 23:27:52 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Custom implementation of ft_memchr to locate a character in a memory block.
 *
 * @param s The memory block to search.
 * @param c The character to find.
 * @param n The number of bytes to search.
 * @return A pointer to the character if found, or NULL otherwise.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n--)
	{
		if (*ptr == (unsigned char) c)
			return ptr;
		ptr++;
	}
	return (NULL);
}

/**
 * @brief Measure string length.
 *
 * @param s The input string.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/**
 * @brief Copies memory area.
 *
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param n Number of bytes to copy.
 * @return Pointer to destination buffer.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

/**
 * @brief Custom implementation of ft_memmove to shift memory safely.
 *
 * @param dst The destination memory.
 * @param src The source memory.
 * @param len The number of bytes to move.
 * @return A pointer to the destination memory.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (d == s || len == 0)
		return (dst);
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		d +=len;
		s += len;
		while (len--)
			*(--d) = *(--s);
	}
	return (dst);
}

/**
 * @brief Custom implementation of ft_strlcpy to safely copy strings.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return The length of the source string.
 */
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i ++;
		}
		dst[i] = '\0';
	}
	return ft_strlen(src);
}

char	*ft_strjoin_gnl(char *existing_text, char *new_text)
{
	size_t	existing_len;
	size_t	new_len;
	char	*combined_text;

	if (!existing_text)
	{
		existing_text = malloc(ft_strlen(new_text) + 1);
		if (!existing_text)
			return (NULL);
		ft_strlcpy_gnl(existing_text, new_text, ft_strlen(new_text) + 1);
		return (existing_text);
	}
	existing_len = ft_strlen(existing_text);
	new_len = ft_strlen(new_text);
	combined_text = malloc(existing_len + new_len + 1);
	if (!combined_text)
		return (existing_text);
	ft_memcpy(combined_text, existing_text, existing_len);
	ft_memcpy(combined_text + existing_len, new_text, new_len);
	combined_text[existing_len + new_len] = '\0';
	free(existing_text);
	return (combined_text);
}
