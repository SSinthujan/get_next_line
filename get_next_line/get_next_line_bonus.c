/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:54:52 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/01/22 05:38:37 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	fill_stash(int fd, char *stash[fd], char *buffer)
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
	static char	*stash[4096];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!fill_stash(fd, &stash[fd], buffer))
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (free(buffer), NULL);
	}
	line = malloc((ft_check(stash[fd]) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash[fd], ft_check(stash[fd]) + 1);
	clean_stash(&stash[fd]);
	free(buffer);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	//char *line;
// 	char *line2;
// 	//int fd;
// 	char *line3;
// 	char *line4;
// 	char *line5;
// 	char *line6;
// 	int i;

// 	//fd = open("texte", O_RDONLY);
// 	int fd2 = open("test.txt", O_RDONLY);
// 	int fd3 = open("test.txt", O_RDONLY);
// 	int fd4 = open("test.txt", O_RDONLY);
// 	int fd5 = open("test.txt", O_RDONLY);
// 	int fd6 = open("test.txt", O_RDONLY);
// 	i = 0;
// 	while (1)
// 	{
// 		//line = get_next_line(0);
// 		//printf("gnl 1 : %s\n", line);
// 		line2 = get_next_line(fd2);
// 		printf("gnl 2 : %s\n", line2);
// 				line3 = get_next_line(fd3);
// 		printf("gnl 3: %s\n", line3);
// 				line4 = get_next_line(fd4);
// 		printf("gnl 4 : %s\n", line4);
// 				line5 = get_next_line(fd5);
// 		printf("gnl 5 : %s\n", line5);
// 				line6 = get_next_line(fd6);
// 		printf("gnl 6 : %s\n", line6);
// 		//if (!line)
// 		//	break ;
// 		if (!line2)
// 			break ;
// 		if (!line3)
// 			break ;
// 		if (!line4)
// 			break ;
// 		if (!line5)
// 			break ;
// 		if (!line6)
// 			break ;
// 		//free(line);
// 		free(line2);
// 		free(line3);
// 		free(line4);
// 		free(line5);
// 		free(line6);
// 		i++;
// 	}
// }