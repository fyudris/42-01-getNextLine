/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:41:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/08 23:50:00 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Finds the position of a newline ('\n') character in a string. Uses ft_memchr for efficiency.
 *
 * @param str The input string to search for a newline character.
 * @return The index of the newline character, or 0 if not found.
 */
size_t	find_newline_index(const char *str)
{
	char	*newline_ptr;

	newline_ptr = ft_memchr(str, '\n', ft_strlen(str));
	if (newline_ptr)
		return ((size_t) (newline_ptr - str + 1));
	else
		return (0);
}

/**
 * @brief Reads from a file descriptor and appends to the buffer.
 *
 * @param fd The file descriptor to read form.
 * @param buffer The buffer to store read characters.
 * @return The number of bytes read, or -1 if an error occurs.
 */
ssize_t	read_into_buffer(int fd, char *buffer)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		temp_buffer[bytes_read] = '\0';
		ft_strlcpy_gnl(buffer + ft_strlen(buffer), temp_buffer, BUFFER_SIZE + 1 - ft_strlen(buffer));
	}
	return (bytes_read);
}

/**
 * @brief Extracts a line from the buffer and dynamically grows the returned string.
 *
 * @param buffer The buffer containing the text
 * @return The extracted line as a dynamically allocated string.
 */
char	*retrieve_line_from_buffer(char *buffer)
{
	size_t	newline_index;
	char	*line;
	char	temp[BUFFER_SIZE + 1];
	size_t	read_bytes;

	newline_index = find_newline_index(buffer);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (newline_index == 0 && buffer[0])
	{
		ft_strlcpy_gnl(temp, buffer, BUFFER_SIZE + 1);
		line = ft_strjoin_gnl(line, temp);
		if (!line)
			return (NULL);
		buffer[0] = '\0';
		read_bytes = read_into_buffer(0, buffer);
		if (read_bytes == 0)
			break ;
		newline_index = find_newline_index(buffer);
	}
	if (buffer[0])
	{
		ft_strlcpy_gnl(temp, buffer, newline_index + 1);
		char *temp_line  = ft_strjoin_gnl(line, temp);
		if (!temp_line)
		{
			free(line);
			return (NULL);
		}
		line = temp_line;
		ft_memmove(buffer, buffer + newline_index, BUFFER_SIZE - newline_index);
		buffer[BUFFER_SIZE - newline_index] = '\0';
	}
	return (*line ? line : NULL);
}

/**
 * @brief Reads and returns the next line from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return A dynamically allocated string containing the next line, or NULL on failure.
 */
char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	ssize_t read_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!find_newline_index(buffer))
	{
		read_status = read_into_buffer(fd, buffer);
		if (read_status == -1)
			return (NULL);
		if (read_status == 0 && buffer[0] == '\0')
			return (NULL);
	}
	return (retrieve_line_from_buffer(buffer));
}

//TODO: Delete this
int	main(void)
{
	char	*filename = "test.txt";
	int		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	char	*line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}