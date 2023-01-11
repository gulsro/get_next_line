/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:39:40 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/09 19:50:03 by gozturk       ########   odam.nl         */
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
	//printf("makestr strlen: %d\n", ft_strlen(str));
	return (str);
}

char	*read_in_buf(int fd)
{
	char	*buf;
	long	n;
	
	buf = make_string(BUFFER_SIZE + 1);
	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0) //!!!!!!
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
	}
	while (1) 
	{
		if (check_newline(rest) == 0)
        	{
			buf = read_in_buf(fd);
		//	printf("rest is :%s\n", rest);
			if (buf != NULL)
			{
				rest = from_buf_to_rest(rest, buf);
			} 
			else if (rest != NULL)
			{
				line = fill_line(rest);
				rest = NULL;
				break;
			}
			continue;
		}
		if (check_newline(rest) == 1)
		{
			line = fill_line(rest);
			rest = shift_rest(rest);
//			printf("rest is :%s\n", rest);
			break ;
		}
	}
	return line;
}

/*
int main()
{
        int fd = open("line_w_nl.txt", O_RDONLY, 0);
        char *line_string;
        for (int i = 0; i < 35; i++)
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
		system("leaks gnl");
}
*/
