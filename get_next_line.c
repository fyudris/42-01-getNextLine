/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:41:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/07 16:42:51 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_eol(char *line)
{
	size_t i;

	i = 0;
	if(!line)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (line[i] == '\n' || line[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

/**
 * @brief Reads data from a file descriptor (fd) and appends it to line until a newline (\n) is found.
 *
 * @param line  string being built to store the full line
 * @param stash buffer holding leftover data from previous read
 * @param eol_post pointer to tract the position of '\n' in the buffer
 * @param fd file descriptor to read from
 */
char	*extract_line(char *line, char *stash, int *eol_post, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	read_check;
	size_t	line_size; // track bytes successfully read from fd ( > 0: success, 0: EOF, -1: Error)
	while (*eol_post == -1)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		read_check = read(fd, buffer, BUFFER_SIZE);

		// printf("📥 [Read %zd bytes]: \"%s\"\n", read_check, buffer);

		if (read_check == -1)
		{
			free(line);
			ft_bzero(stash, BUFFER_SIZE + 1);
			return (NULL);
		}
		line_size = find_eol(buffer);
		ft_strlcpy_gnl(stash, &buffer[line_size], (BUFFER_SIZE + 1));

		// printf("🗄️ [Updated Stash]: \"%s\"\n", stash);

		buffer[line_size] = '\0';

		// printf("📌 [Buffer to Append]: \"%s\"\n", buffer);

		line = ft_strjoin_gnl(line, buffer, eol_post);

		// printf("✍️ [Updated Line]: \"%s\"\n", line);

		if (read_check == 0)
		{
			ft_bzero(stash, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line);
}

/**
 * @brief Look for the first occurence of '\n' in the stash
 */
char	*init_line(char *stash, int *eol_post)
{
	size_t	len;
	char	*line;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	if (len > 0 && line[len - 1] == '\n')
		*eol_post = len - 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			eol_post;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	eol_post = -1;

	// printf("\n🔹 [Before init_line] stash: \"%s\"\n", stash);
	line = init_line(stash, &eol_post);
	// printf("🔹 [After init_line] Extracted Line: \"%s\", eol_post: %d\n", line ? line : "NULL", eol_post);

	if (!line)
		return (NULL);
	ft_strlcpy_gnl(stash, &stash[eol_post + 1], BUFFER_SIZE + 1);
	line = extract_line(line, stash, &eol_post, fd);
	if (!line || line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}

// int main(void)
// {
//     int		fd;
//     char	*line;
// 	char	*filename = "text1.txt";

//     // Open the file in read-only mode
//     fd = open(filename, O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }

// 	printf("\n📌 Reading from file: %s\n\n", filename);

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("➡ Line: %s", line);
//         free(line);
//     }

//     // Close the file
//     close(fd);

//     printf("\n✅ Finished reading file!\n");
//     return (0);
// }
