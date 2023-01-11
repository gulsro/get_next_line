/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:21:42 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/09 18:36:25 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 5
//#endif

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
size_t	newline_pos(char *buffy);
char	*make_string(size_t length);
char	*shift_rest(char *rest);
char	*fill_line(char *rest);
char	*from_buf_to_rest(char *rest, char *buf);
char	*read_in_buf(int fd);
size_t	check_newline(char *buf);

#endif
