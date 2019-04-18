#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

static int	split_buff(char **str, char **line, int fd)
{
    char	    *left;
    char	    *right;
    int		    i;
    int		    j;

    i = 0;
    j = ft_strlen(str[fd]);
    while (str[fd][i] != '\n' && str[fd][i])
	i++;
    if (!(left = (char*)malloc(i + 1)))
	return (-1);
    ft_memcpy(left, str[fd], i);
    left[i] = '\0';
    *line = left;
    if (i == j)
	return (0);
    if (!(right = (char*)malloc(j - i + 1)))
	return (-1);
    ft_memcpy(right, (str[fd] + i + 1), j - i);
    right[j - i] = '\0';
    free(str[fd]);
    str[fd] = right;
    return (1);
}

int		get_next_line(const int fd, char **line)
{
    static char	    *str[100];
    char	    *tmp;
    char	    buff[BUFF_SIZE + 1];
    int		    ret;

    ret = 1;
    if (!str[fd])
	str[fd] = ft_strnew(1);
    while (ft_strchr(str[fd], '\n') == NULL && ret) 
    {
	if((ret = read(fd, buff, BUFF_SIZE)) < 0)
	    return (-1);
	buff[ret] = '\0';
	tmp = str[fd];
	str[fd] = ft_strjoin(str[fd], buff);
	free(tmp);
    }
    split_buff(str, line, fd);
    if (ret == 0)
    {
	free(str[fd]);
	return (0);
    }
    return (1);
}
