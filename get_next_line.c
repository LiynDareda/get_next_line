#include "get_next_line.h"	

static char	*next_line(int fd, char *buffer, char *buffer_static)
{
	int		read_line;
	char	*tmp;

	read_line = 1;
	while (read_line > 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		if (!buffer_static)
			buffer_static = ft_strdup("");
		tmp = buffer_static;
		buffer_static = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer_static);
}

static char	*extract(char *buffer_static)
{
	size_t	count;
	char	*buffer;

	count = 0;
	while (buffer_static[count] != '\n' && buffer_static[count] != '\0')
		count++;
	if (buffer_static[count] == '\0' || buffer_static[1] == '\0')
		return (0);
	buffer = ft_substr(buffer_static, count + 1, ft_strlen(buffer_static) - count);
	if (!buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*buffer_static;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer_static = next_line(fd, buffer, buffer_static);
	free(buffer);
	buffer = NULL;
    line = extract(buffer_static);
	if (!line)
		return (NULL);
	return (line);
}
