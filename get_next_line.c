/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaalmoui <yaalmoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 12:05:35 by yaalmoui          #+#    #+#             */
/*   Updated: 2026/09/25 18:45:38 by yaalmoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*saved;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (read_file(fd, &saved, buffer) == -1)
		return(free(buffer), free(saved), saved = NULL, NULL);
	free(buffer);
	if (!saved || saved[0] == '\0')
		return (free(saved), saved = NULL, NULL);
	line = extract_line(saved);
	if (!line)
		return (free(saved), saved = NULL, NULL);
	saved = updated_saved(saved);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;

// 	count = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file\n");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 			break;
// 		count++;
// 		printf("[%d]: %s", count, next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }
