#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

int	main(void)
{
    int	    fd1;
    int	    fd2;
    int	    fd3;
    char    *line1;
    char    *line2;
    char    *line3;
    int	    i;

    i = 0;
    fd1 = open("get_next_line.h", O_RDONLY);
    fd2 = open("get_next_line.c", O_RDONLY);
    fd3 = open("libft.h", O_RDONLY);
//    while ((i = get_next_line(fd1, &line1)) == 1)
//    {
//	printf("%s\n", line1);
//	free(line1);
//    }

    while (i < 10)
    {
	get_next_line(fd1, &line1);
	printf("1-%d-%s\n",i, line1);
	get_next_line(fd2, &line2);
	printf("2-%d-%s\n",i, line2);
	get_next_line(fd3, &line3);
	printf("3-%d-%s\n",i, line3);
	free(line1);
	free(line2);
	free(line3);
	i++;
    }
    close(fd1);
    close(fd2);
  return (0);
}
