/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:57:34 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/01/22 05:38:44 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char *s);
size_t	ft_check(char *s);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2, int len);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_strchr(char *s, int c);
int		fill_stash(int fd, char *stash[fd], char *buffer);
void	clean_stash(char **stash);
char	*get_next_line(int fd);

#endif