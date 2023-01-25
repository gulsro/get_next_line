/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 11:31:09 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/25 12:38:09 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_newline(char *buf)
{
	size_t	n;

	n = 0;
	if (!buf || ft_strlen(buf) == 0)
		return (0);
	while (buf[n] != '\0')
	{
		if (buf[n] == '\n')
			return (n);
		n++;
	}
	return (0);
}

char	*fill_line(char *stash)
{
	char	*filled_line;
	size_t	i;

	i = 0;
	filled_line = make_string(ft_strlen(stash) + 1);
	if (!filled_line)
		return (NULL);
	while (stash[i] != '\0')
	{
		filled_line[i] = stash[i];
		if (filled_line[i] == '\n')
			break ;
		i++;
	}
	return (filled_line);
}

char	*shift_stash(char *stash)
{
	char	*shifted;
	size_t	i_stash;
	size_t	i_shift;
	size_t	pos;

	i_stash = 0;
	i_shift = 0;
	pos = check_newline(stash);
	if (pos == ft_strlen(stash))
		return (free(stash), NULL);
	shifted = make_string(ft_strlen(stash) - pos);
	if (!shifted)
		return (free(stash), NULL);
	while (stash[i_stash] != '\0')
	{
		if (stash[i_stash] == '\n')
		{
			i_stash++;
			while (stash[i_stash] != '\0')
				shifted[i_shift++] = stash[i_stash++];
			break ;
		}
		i_stash++;
	}
	return (free(stash), shifted);
}

char	*from_buf_to_stash(char *prev_stash, char *buf)
{
	char	*new_stash;
	size_t	stash_i;
	size_t	buf_i;

	buf_i = 0;
	stash_i = 0;
	if (prev_stash == NULL)
	{
		prev_stash = make_string(BUFFER_SIZE + 1);
		if (!prev_stash)
			return (NULL);
	}
	new_stash = make_string(ft_strlen(prev_stash) + BUFFER_SIZE + 1);
	if (!new_stash)
		return (free(prev_stash), NULL);
	while (prev_stash[stash_i] != '\0')
	{
		new_stash[stash_i] = prev_stash[stash_i];
		stash_i++;
	}
	while (buf[buf_i] != '\0')
		new_stash[stash_i++] = buf[buf_i++];
	new_stash[stash_i] = '\0';
	return (free(prev_stash), new_stash);
}
