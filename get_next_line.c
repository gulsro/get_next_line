/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:39:40 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/12 16:59:40 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char *make_string(size_t length)
{
	char *str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * length);
	if (!str) 
		return NULL;
	while (i < length)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*read_in_buf(int fd)
{
	char	*buf;
	long	n;
	
	buf = make_string(BUFFER_SIZE + 1);
	if (buf == NULL)
		return NULL;
	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buf);
		return NULL;
	}
	buf[n] = '\0';
	return buf;
}

char	*get_next_line(int fd)
{
	char	*buf;
	static char	*rest;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = make_string(BUFFER_SIZE + 1);
		if (rest == NULL)
			return NULL;
	}
	while (1) 
	{
		if (check_newline(rest) == 0)
        {
			buf = read_in_buf(fd);
			if (buf != NULL)
				rest = from_buf_to_rest(rest, buf);
			else if (rest != NULL)
			{
				line = fill_line(rest);
				rest = NULL;
				break;
			}
		}
		else if (check_newline(rest) == 1)
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
        int fd = open("empty.txt", O_RDONLY, 0);
        char *line_string;
        for (int i = 0; i < 6; i++)
        {
			line_string = get_next_line(fd);
			if (line_string == NULL)
			{	
				break ;
			}
			printf("%s", line_string);
			free(line_string);
        }
        close(fd);
		system("leaks a.out");
}
*/
