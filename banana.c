#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//#define BUFFER_SIZE 100

size_t	newline_pos(char *buffy)
{
	size_t	i;

	i = 0;
	while (buffy[i] != '\n')
	{
		i++;
	}
	return i;
}

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
char	*shift_rest(char *rest)
{
	static char	*shifted;
	size_t	i_rest;
	size_t 	i_shift;
	
	i_rest = 0;
	i_shift = 0;
	
	shifted = make_string(strlen(rest) - newline_pos(rest));
	
	if (!shifted)
		return NULL;
	while (rest[i_rest] != '\0')
	{
		if (rest[i_rest] == '\n')
		{
			i_rest++;
			while (rest[i_rest] != '\0')
			{
			
				shifted[i_shift] = rest[i_rest];
				i_shift++;
				i_rest++;
			}
			break ;
		}
		i_rest++;
	}
	free(rest);
	return shifted;
}

char	*fill_line(char *rest)
{
	char	*line;
	size_t	i;

	i = 0;
	line = make_string(strlen(rest) + BUFFER_SIZE + 1);
//	line = make_string(strlen(rest));
//	line = make_string(newline_pos(rest) + 1);

	if (!line)
		return NULL;
	while (1)
	{
		line[i] = rest[i];
		if(line[i] == '\n'){
			break;
		}
		i++;
	}
	return line;
}

char    *from_buf_to_rest(char *rest, char *buf)
{
 	static char	*filled_rest;
 	size_t     rest_index;
	size_t     buf_index;

	buf_index = 0;
	rest_index = 0;
	filled_rest = make_string(strlen(rest) + BUFFER_SIZE + 1);
	while (strlen(rest) > 0 && rest[rest_index] != '\0')
	{
		filled_rest[rest_index] = rest[rest_index];
		rest_index++;
	}
	while (buf[buf_index] != '\0')
	{
		filled_rest[rest_index] = buf[buf_index];
		rest_index++;
		buf_index++;
	}
	filled_rest[rest_index] = '\0';
	free(rest);
	return filled_rest;
}

size_t     check_newline(char *buf)
{
        size_t     n;

        n = 0;
        if (!buf || strlen(buf) == 0)
                return 0;
        while (buf[n] != '\0')
        {
                if (buf[n] == '\n')
                        return 1;
                n++;
        }
        return 0;
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
		buf=NULL;
	}
	else 
	{
                buf[n] = '\0';
	}
	return buf;
}

char	*get_next_line(size_t fd)
{
	char	*buf;
	static char	*rest;
	char	*line;
	size_t n;
	
	if (fd < 0 || BUFFER_SIZE < 0)
		return NULL;
	if (!rest)
		rest = make_string(BUFFER_SIZE + 1);
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



int main()
{
        size_t fd = open("alice.txt", O_RDONLY, 0);
        char *line_string;
        line_string = NULL;
        for (size_t i = 0; i < 280; i++)
        {
                line_string = get_next_line(fd);
				printf("%s", line_string);
                free(line_string);
        }
        close(fd);
}
