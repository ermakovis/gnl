#include "libft.h"
#include "get_next_line.h"

int	main(void)
{
    int	    fd;
    int	    fd1;
    char    *line;
    char    *line1;
    int	    i;
    int	    n;
    int	    n2;

    i = 0;
    n = 0;
    n2 = 0;
    fd = open("test", O_RDONLY);
    fd1 = open("get_next_line.h", O_RDONLY);
    get_next_line(fd, &line);
    get_next_line(fd, &line);
    get_next_line(fd, &line);
    while (i < 200)
    {
	if ((n = get_next_line(fd, &line)))
	{
	    printf("%d - %s\n", n, line); 
	    free(line);
	}
	if ((n2 = get_next_line(fd1, &line1)))
	{
	    printf("%d - %s\n", i, line1);
	    free(line1);
	}
	i++;
    }
}
