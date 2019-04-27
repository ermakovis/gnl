#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
//!!!!!!!!!!!!!!!!!!!!
# include <stdio.h>
//!!!!!!!!!!!!!!!!!!!!
# define BUFF_SIZE 10000 

typedef struct	s_bf
{
    char	*buff;
    int		fd;
}		t_bf;

int	get_next_line(const int fd, char **line);

#endif
