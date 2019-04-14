#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "displ.h"

char	*ft_readline(const int fd, char **line)
{
    static char	    *str;
    char	    *tmp;
    char	    buff[BUFF_SIZE];
    int		    ret;

    if (!str)
	str = (char*)malloc(0);
    while (ft_strchr(str, '\n') == NULL) 
    {
	if((ret = read(fd, buff, BUFF_SIZE)) < 0)
	    break ;
	buff[ret] = '\0';
	tmp = str;
	str = ft_strjoin(str, buff);
	free(tmp);
    }

    *line = str;
    return (NULL);
}

int	main(int argc, char **argv)
{
    int	    fd;
    char    *line;
    if (argc != 2)
	return (0);
    fd = open(argv[1], O_RDONLY);
    ft_readline(fd, &line);
    printf("%s\n\n\n", line);
    ft_readline(fd, &line);
    printf("%s\n\n\n", line);
    ft_readline(fd, &line);
    printf("%s\n\n\n", line);
    free(line);
    return (0);
}
