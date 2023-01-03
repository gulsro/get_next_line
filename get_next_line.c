/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 1723/01/03 09:39:46 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/03 17:34:54 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

char	*fill_line(char *line, char *stash)
{
	int	index;

	index = 0;
	if(!stash)
		return NULL;
	while (stash[index] != '\n')
	{
		line[index] = stash[index];
		index++;
	}

	line[index] = '\n';
	line[index + 1] = '\0';
	return (line);
}

char	*fill_stash(char *stash, char *buf)
{
	char	*ptr;
	int		stash_len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	stash_len = strlen(stash) + 1;
	ptr = stash;
	while (i < stash_len)
	{	
		ptr[i] = stash[i];
		i++;
	}
	while (i < (int)(stash_len + strlen(buf) + 1))
	{
		ptr[i - 1] = buf[j];
		i++;
		j++;
	}
	return (stash);
}

char	*trim_stash(char *stash)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stash[i] != '\n')
		i++;
	i++;
	while (stash[j] != '\0')
	{
		stash[j] = stash[i]; 
		i++;
		j++;
	}
	stash[j] = '\0';
	return (stash);
}

int	if_newline_exists(char *stash)
{
	int	search_newline;
	
	search_newline = 0;
	if (!stash)
		return 0;
	while (stash[search_newline] != '\0')
	{
		if (stash[search_newline] == '\n')
			return 1;
		search_newline++;
	}
	return 0;
}

char	*get_next_line(int fd)
{
	char	buf[2 + 1];
	static char	stash[2];
	char *line;
	int	n;

	n = read(fd, buf, 2);
	buf[n] = '\0';
	if (n > 0)
	{
		fill_stash(stash, buf);
		while (if_newline_exists(stash) == 0)
		{
			n = read(fd, buf, 2);
			buf[n] = '\0';
			fill_stash(stash, buf);
		}
		if (if_newline_exists(stash) == 1)
		{	
			line = malloc(sizeof(char) * 2 + 1);
			if (!line)
				return NULL;
			fill_line(line, stash);
		}
		trim_stash(stash);
	}
	return (line);
}

int main()
{
	int fd = open("alice.txt", O_RDONLY, 0);
	char *line_string;
	line_string = NULL;
	for (int i = 0; i < 3; i++)
	{
		line_string = get_next_line(fd);
		printf("%s", line_string);
		free(line_string);
	}
	close(fd);
}
