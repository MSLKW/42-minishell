/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:13:14 by yilim             #+#    #+#             */
/*   Updated: 2024/05/09 21:13:14 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	char		*res;
	static char	*line;

	if (fd == -1 || read(fd, NULL, 0) == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
	{
		line = (char *)malloc(sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	res = get_res(line);
	line = next_line(line);
	return (res);
}

char	*read_line(int fd, char *line)
{
	char	*buf;
	int		status;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	status = 1;
	while (status > 0)
	{
		ft_memset(buf, 0, BUFFER_SIZE + 1);
		status = read(fd, buf, BUFFER_SIZE);
		if (status == -1)
		{
			free(buf);
			return (NULL);
		}
		line = join_line(line, buf);
		if (check_end_index(line) != -1)
			break ;
	}
	free(buf);
	return (line);
}

char	*join_line(char *line, char *buf)
{
	char	*res;

	res = ft_strjoin(line, buf);
	free(line);
	return (res);
}

char	*get_res(char *line)
{
	char	*res;
	int		end_i;

	if (line[0] == '\0')
		return (NULL);
	end_i = check_end_index(line);
	if (end_i != -1)
		res = ft_substr(line, 0, end_i + 1);
	else
		res = ft_substr(line, 0, ft_strlen(line));
	return (res);
}

char	*next_line(char *line)
{
	char	*res;
	int		end_i;

	end_i = check_end_index(line);
	if (end_i != -1)
		res = ft_substr(line, end_i + 1, ft_strlen(line) - end_i - 1);
	else
		res = NULL;
	free(line);
	return (res);
}
