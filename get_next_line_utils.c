/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 13:26:59 by gozturk       #+#    #+#                 */
/*   Updated: 2023/01/12 18:16:17 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

size_t     check_newline(char *buf)
{
        size_t     n;

        n = 0;
        if (!buf || ft_strlen(buf) == 0)
                return 0;
        while (buf[n] != '\0')
        {
                if (buf[n] == '\n')
                        return 1;
                n++;
        }
        return 0;
}

char	*shift_rest(char *rest)
{
	static char	*shifted;
	size_t	i_rest;
	size_t 	i_shift;

	i_rest = 0;
	i_shift = 0;
	shifted = make_string(ft_strlen(rest) - newline_pos(rest));
	if (!shifted)
	{
		free(rest);
		return ( NULL);
	}
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
	if (rest == NULL || ft_strlen(rest) == 0)
	{
		free(rest);
		rest = NULL;
		return NULL;
	}
	line = make_string(ft_strlen(rest) + BUFFER_SIZE + 1);
	if (!line)
	{
		free(rest);
		rest = NULL;
		return NULL;
	}
	while (rest[i] != '\0')
	{
		line[i] = rest[i];
		if(line[i] == '\n')
			break;
		i++;
	}
	free(rest);
	rest = NULL;
	return line;
}

char    *from_buf_to_rest(char *rest, char *buf)
{
 	static char	*filled_rest;
 	size_t     rest_index;
	size_t     buf_index;

	buf_index = 0;
	rest_index = 0;
	if (buf == NULL && ft_strlen(rest) == 0)
	{
		free(rest);
		return NULL;
	}
	filled_rest = make_string(ft_strlen(rest) + BUFFER_SIZE + 1);
	if (!filled_rest)
		return (free(rest), free(buf), NULL);
	while (ft_strlen(rest) > 0 && rest[rest_index] != '\0')
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
	free(buf);
	return filled_rest;
}
