/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaalmoui <yaalmoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 18:43:30 by yaalmoui          #+#    #+#             */
/*   Updated: 2026/09/25 18:50:15 by yaalmoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

char	*extract_line(char *saved)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		len = i + 2;
	else
		len = i + 1;
	line = malloc(len);
	if (!line)
		return (NULL);
	ft_strlcpy(line, saved, len);
	return (line);
}

char	*updated_saved(char *saved)
{
	int		i;
	int		remainder;
	char	*tmp;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
	{
		remainder = ft_strlen(saved) - i;
		tmp = malloc(remainder);
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, saved + i + 1, remainder);
		free(saved);
		saved = tmp;
	}
	else
	{
		free(saved);
		saved = NULL;
	}
	return (saved);
}

static int	read_file(int fd, char **saved, char *buffer)
{
	int		count;
	char	*tmp;

	count = 1;
	while ((!*saved || !ft_strchr(*saved, '\n')) && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (-1);
		buffer[count]= '\0';
		tmp = ft_strjoin(*saved, buffer);
		free(*saved);
		*saved = tmp;
		if (!*saved)
			return(-1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*saved[MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (read_file(fd, &saved[fd], buffer) == -1)
		return(free(buffer), free(saved[fd]), saved[fd] = NULL, NULL);
	free(buffer);
	if (!saved[fd] || saved[fd][0] == '\0')
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	line = extract_line(saved[fd]);
	if (!line)
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	saved[fd] = updated_saved(saved[fd]);
	return (line);
}
