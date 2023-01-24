#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <unistd.h>
# include <string.h>
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
