#ifndef	GET_NEXT_LINE_H
#define	GET_NEXT_LINE_H

#ifndef	BUFFER_SIZE
#define	BUFFER_SIZE 5
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

char    *get_next_line(int fd);
size_t ft_strlen(char *str);
int     if_newline_exists(char *stash);
char    *fill_line(char *stash);
char    *fill_stash(char *stash, char *buf);
char    *trim_stash(char *stash);

#endif
