/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 11:31:18 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/25 11:37:18 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
char	*free_stash(char *stash);
char	*make_string(size_t length);
char	*shift_stash(char *stash);
char	*fill_line(char *stash);
char	*from_buf_to_stash(char *stash, char *buf);
char	*read_in_buf(int fd, char *stash);
size_t	check_newline(char *buf);

#endif
