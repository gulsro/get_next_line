#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*free_stash(char *stash)
{
	free(stash);
	stash = NULL;
	return (stash);
}

char	*make_string(size_t length)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	while (i < length)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*read_from_file(int fd, char *stash)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	n;

	while (1)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
		{
			if (stash)
				stash = free_stash(stash);
			break ;
		}
		if (n > 0)
		{
			buf[n] = '\0';
			stash = from_buf_to_stash(stash, buf);
		}
		if (n == 0 || check_newline(stash) != 0)
			break ;
	}
	if (stash && ft_strlen(stash) == 0)
		stash = free_stash(stash);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (check_newline(stash) == 0)
		stash = read_from_file(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = fill_line(stash);
	if (!line)
		return (free(stash), NULL);
	stash = shift_stash(stash);
	return (line);
}
/*
 int main()
 {
	 int fd = open("alice.txt", O_RDONLY, 0);
	 char *line_string;
	 for (int i = 0; i < 10; i++)
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
 //              system("leaks a.out");
 }*/
