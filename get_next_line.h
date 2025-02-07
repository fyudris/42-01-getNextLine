/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:44:55 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/07 16:09:25 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

// TODO: Remove this
#include <fcntl.h>
#include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*extract_line(char *line, char *stash, int *eol_post, int fd);
char	*init_line(char *stash, int *eol_post);
size_t	find_eol(char *line);

void	*ft_memcpy(void *dst, void *src, size_t n);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin_gnl(char *line, char *buffer, int *eol_post);
void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);

#endif
