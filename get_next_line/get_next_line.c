/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:57:44 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/01/22 05:39:02 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_check(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

int	fill_stash(int fd, char **stash, char *buffer)
{
	int	len;

	len = read(fd, buffer, BUFFER_SIZE);
	if (len < 0)
		return (0);
	*stash = ft_strjoin(*stash, buffer, len);
	if (!len && !ft_strlen(*stash))
		return (0);
	while (!(ft_strchr(buffer, '\n')) && len)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0)
			return (0);
		*stash = ft_strjoin(*stash, buffer, len);
	}
	return (1);
}

void	clean_stash(char **stash)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	i = 0;
	j = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i])
		i++;
	while ((*stash)[i])
		(*stash)[j++] = (*stash)[i++];
	(*stash)[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!fill_stash(fd, &stash, buffer))
	{
		free(stash);
		stash = NULL;
		return (free(buffer), NULL);
	}
	line = malloc((ft_check(stash) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, ft_check(stash) + 1);
	clean_stash(&stash);
	free(buffer);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	int i;

// 	fd = open("test2", O_RDONLY);
// 	i = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%d : %s", i, line);
// 		if (!line)
// 			break ;
// 		free(line);
// 		i++;
// 	}
// }