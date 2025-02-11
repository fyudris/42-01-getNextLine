/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:20:49 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/11 18:37:31 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../get_next_line.h"

/*
 * Helper function: Attempts to open `filename` for reading,
 * calls get_next_line in a loop until it returns NULL,
 * and prints each line to stdout.
 */
static void test_file_read(const char *filename)
{
    int     fd;
    char    *line;

    printf("=== Testing file: %s ===\n", filename);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        // If open fails, just report and return
        perror("open");
        return;
    }

    // Repeatedly call get_next_line until it returns NULL
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("GNL returned: %s", line); // `line` already has newline if present
        free(line);
    }

    if (close(fd) == -1)
        perror("close");
    printf("=== End of file: %s ===\n\n", filename);
}

/*
 * Helper function: Simply calls get_next_line() on a provided FD
 * and prints the result or "NULL".
 */
static void test_fd_read(int fd, const char *test_name)
{
    char *line;

    printf("=== Testing FD: %d (%s) ===\n", fd, test_name);
    line = get_next_line(1);
    if (line == NULL)
        printf("get_next_line returned: NULL\n");
    else
    {
        printf("get_next_line returned: %s", line);
        free(line);
    }
    printf("=== End FD: %d ===\n\n", fd);
}

/*
 * A helper function that interleaves calls to get_next_line() on three
 * different file descriptors (fd1, fd2, fd3). This demonstrates the
 * "multiple FD" behavior required by the bonus.
 */
//  static void test_multiple_fds(void)
//  {
//      int   fd1, fd2, fd3;
//      char  *line1, *line2, *line3;

//      printf("\n=== Testing multiple FDs simultaneously (bonus) ===\n");

//      fd1 = open("multi_fd_1.txt", O_RDONLY);
//      fd2 = open("multi_fd_2.txt", O_RDONLY);
//      fd3 = open("multi_fd_3.txt", O_RDONLY);

//      // If any file failed to open, just report and return
//      if (fd1 < 0 || fd2 < 0 || fd3 < 0)
//      {
// 	 perror("open");
// 	 if (fd1 >= 0) close(fd1);
// 	 if (fd2 >= 0) close(fd2);
// 	 if (fd3 >= 0) close(fd3);
// 	 return;
//      }

//      /*
//       * We keep reading line-by-line from each FD, one after the other,
//       * until all three return NULL in the same iteration.
//       */
//      while (1)
//      {
// 	 line1 = get_next_line(fd1);
// 	 line2 = get_next_line(fd2);
// 	 line3 = get_next_line(fd3);

// 	 // If all three are NULL, we're done with all files
// 	 if (!line1 && !line2 && !line3)
// 	     break;

// 	 // Print results from fd1
// 	 if (line1)
// 	 {
// 	     printf("[FD1] %s", line1); // line1 might already contain a newline
// 	     free(line1);
// 	 }
// 	 else
// 	     printf("[FD1] <NULL>\n");

// 	 // Print results from fd2
// 	 if (line2)
// 	 {
// 	     printf("[FD2] %s", line2);
// 	     free(line2);
// 	 }
// 	 else
// 	     printf("[FD2] <NULL>\n");

// 	 // Print results from fd3
// 	 if (line3)
// 	 {
// 	     printf("[FD3] %s", line3);
// 	     free(line3);
// 	 }
// 	 else
// 	     printf("[FD3] <NULL>\n");

// 	 printf("---------------------------------\n");
//      }

//      close(fd1);
//      close(fd2);
//      close(fd3);
//      printf("=== End of multiple FDs test ===\n\n");
//  }


/*
 * The main entry point:
 * 1) Tests a "normal" file with multiple lines
 * 2) Tests an empty file
 * 3) Tests a non-existent file (should trigger open() error)
 * 4) Tests a negative FD
 */
int main(void)
{
    // 1) Test reading from a file with multiple lines
    //    Create or adjust the file "multi_lines.txt" as needed.
    test_file_read("multi_lines.txt");

    // 2) Test reading from an empty file
    //    Make sure "empty.txt" is truly empty!
    test_file_read("empty.txt");

    // 3) Test reading from a file that doesn't exist
    //    This will fail open(), so no lines are read.
    test_file_read("does_not_exist.txt");

    // 4) Test reading from an invalid FD (negative)
    //    This should fail your error checks and return NULL immediately.
    test_fd_read(-1, "negative FD test");

//     test_multiple_fds();
    return 0;
}
