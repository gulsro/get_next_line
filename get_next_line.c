/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:39:40 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/09 14:41:34 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *make_string(size_t length)
{
	char *str;
	str = malloc(sizeof(char) * length);
	if (!str) 
	{
		return NULL;
	}
	bzero(str, length);
	return str;
}

char	*read_in_buf(int fd)
{
	char	*buf;
	size_t	n;
	
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return NULL;
	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buf);
		return NULL;
	}
	else;
		buf[n] = '\0'; 
	return buf;
}

char	*get_next_line(int fd)
{
	char	*buf;
	static char	*rest;
	char	*line;
	
	if (fd < 0 || BUFFER_SIZE < 0)
		return NULL;
	if (!rest)
	{
		rest = make_string(BUFFER_SIZE + 1);
	}
	while (1) 
	{
		if (check_newline(rest) == 0)
        {
			buf = read_in_buf(fd);
			rest = from_buf_to_rest(rest, buf);
			continue;
		}
		if (check_newline(rest) == 1)
		{
			line = fill_line(rest);
			rest = shift_rest(rest);
			break ;
		}
	}
	return line;
}
/*
int main()
{
        int fd = open("alice.txt", O_RDONLY, 0);
        char *line_string;
        for (int i = 0; i < 280; i++)
        {
                line_string = get_next_line(fd);
				if (line_string == NULL)
				{
					free(line_string);	
					break ;
				}
				printf("%s", line_string);
                free(line_string);
        }
        close(fd);
}
*/
