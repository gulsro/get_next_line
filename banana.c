#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//#define BUFFER_SIZE 100
char *make_string(int length)
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
	int	i_rest;
	int 	i_shift;
	
	i_rest = 0;
	i_shift = 0;
	
	shifted = make_string(strlen(rest) + BUFFER_SIZE + 1);
	
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
	int	i;

	i = 0;
	
	line = make_string(strlen(rest) + BUFFER_SIZE + 1);
	
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
 	int     rest_index;
        int     buf_index;

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

int     check_newline(char *buf)
{
        int     n;

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

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	static char	*rest;
	char	*line;
	int n;
	
	if (!rest)
	{
		//rest = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		//bzero(rest, BUFFER_SIZE + 1);
		rest = make_string(BUFFER_SIZE + 1);
	}
        while (1) 
	{
		if (check_newline(rest) == 0)
        	{
                	n = read(fd, buf, BUFFER_SIZE);
			printf("Neler oliyi :%d", n);
			//daha robust yaz. n kontrolu vs.
			buf[n] = '\0';
                	rest = from_buf_to_rest(rest, buf); //FREE ET
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
        int fd = open("alice.txt", O_RDONLY, 0);
        char *line_string;
        line_string = NULL;
        for (int i = 0; i < 1070; i++)
        {
                line_string = get_next_line(fd);
		printf("%s", line_string);
                free(line_string);
        }
        close(fd);
}
