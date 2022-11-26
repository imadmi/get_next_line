/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:22:20 by imimouni          #+#    #+#             */
/*   Updated: 2022/11/26 20:53:53 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_alloc(char	**buff)
{
	*buff = malloc(BUFFER_SIZE + 1);
	if (!*buff)
		return (NULL);
	return (*buff);
}

char	*get_next_line(int fd)
{
	static char	*temporary;
	char		*buff;
	char		*line;
	int			len_readed;
	int			bytes_to_newline;

	buff = ft_alloc(&buff);
	if (!temporary)
		temporary = ft_strdup("");
	len_readed = read(fd, buff, BUFFER_SIZE);
	while (len_readed >= 0)
	{
		buff[len_readed] = 0;
		temporary = ft_strjoin(temporary, buff);
		bytes_to_newline = bytes_to_new_line(temporary);
		if (bytes_to_newline != -1)
			return (free(buff), get__line(&line, &temporary, bytes_to_newline));
		if ((len_readed == 0) && !temporary[0])
			break ;
		if (len_readed == 0)
			return (free(buff), get_the_rest(&temporary, 0));
		len_readed = read(fd, buff, BUFFER_SIZE);
	}
	ft_ffree(&temporary);
	return (free(buff), NULL);
}

char	*get__line(char **line, char **temporary, int bytes_to_newline)
{
	*line = ft_substr(*temporary, 0, bytes_to_newline + 1);
	*temporary = get_the_rest(temporary, bytes_to_newline + 1);
	return (*line);
}

char	*get_the_rest(char **str, int bytes_to_newline)
{
	char	*rest;
	int		restlen;

	restlen = ft_strlen(*str + bytes_to_newline);
	rest = ft_substr(*str, bytes_to_newline, restlen);
	free(*str);
	*str = NULL;
	return (rest);
}

int	bytes_to_new_line(char *temporary)
{
	int	i;

	i = 0;
	while (temporary[i])
	{
		if (temporary[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// cc  -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c && ./a.out
// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	system("clear");
// 	char	*line;
// 	int	fd = open("test", O_WRONLY | O_CREAT);
// 	write(fd,"Imad\nOuss\nLmax\nAhmed\nMimouni\n",28);
// 	fd = open("test", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 	}
// 	close(fd);
// /**/
// 	// int fd = open("test",O_RDWR);
// 	// write(fd,"123456789",10);
// 	// printf("%d\n",fd);
// 	// fd = open("test",O_RDONLY);
// 	// printf("%d\n",fd);
// 	// printf("%s",get_next_line(fd));
// /**/
// 	return (0);
// }