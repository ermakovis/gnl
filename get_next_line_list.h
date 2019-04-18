#ifndef FT_DISPLAY_FILE_H
# define FT_DISPLAY_FILE_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 1

typedef struct	    s_buff
{
    char	    *str;
    int		    fd;
    struct s_buff   *next;
}		    t_buff;

int	get_next_line(const int fd, char **line);

#endif
