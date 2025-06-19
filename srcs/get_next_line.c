/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:20:50 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 23:28:41 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readfile(int fd, char *stash)
{
	char	*buffer;
	int		rdbyte;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	rdbyte = 1;
	while (rdbyte > 0)
	{
		rdbyte = read(fd, buffer, BUFFER_SIZE);
		if (rdbyte == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[rdbyte] = '\0';
		stash = ft_strjoin_free(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (stash);
}

char	*get_line(char *stash)
{
	char	*line;
	int		len;

	if (!stash || stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] != '\n' && stash[len] != '\0')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_substr(stash, 0, len);
	return (line);
}

char	*process_stash(char *stash)
{
	char	*new_stash;
	int		i;

	i = 0;
	if (!stash || stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	else if (stash[i] == '\n')
		i++;
	new_stash = ft_substr(stash, i, ft_strlen(stash));
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = ft_readfile(fd, stash);
	line = get_line(stash);
	stash = process_stash(stash);
	return (line);
}

/* #include <stdio.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	// int		fd2;
	// int		fd3;
	fd1 = open("/Users/zernest/code/get_next_line/tests/test.txt", O_RDONLY);
	// fd2 = open("tests/test2.txt", O_RDONLY);
	// fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		// line = get_next_line(fd2);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// line = get_next_line(fd3);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		i++;
	}
	close(fd1);
	// close(fd2);
	// close(fd3);
	return (0);
} */