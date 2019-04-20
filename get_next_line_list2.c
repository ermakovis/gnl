#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

static void	remove_list(t_buff **lst, int fd)
{
    t_buff	*current;
    t_buff	*last;
    t_buff	*tmp;

    current = *lst;
    while (current)
    {
	if (current->fd == fd)
	{
	    if (current == *lst)
		*lst = current->next;
	    else
		last->next = current->next;
	    tmp = current;
	    current = current->next;
	    free(tmp->str);
	    free(tmp);
	}
	else
	{
	    last = current;
	    current = current->next;
	}
    }
}

static int	find_list(t_buff **tlst, t_buff *lst, int fd)
{
    while (lst)
    {
	if (lst->fd == fd)
	{
	    *tlst = lst;
	    return (1);
	}
	lst = lst->next;
    }
    return (0);
}

static t_buff	*add_list(t_buff **lst, int fd)
{
    t_buff	*new;
    t_buff	*tmp;

    tmp = *lst;
    if(!(new = (t_buff*)malloc(sizeof(t_buff))))
	exit (0) ;
    new->fd = fd;
    new->str = ft_strnew(1);
    if (tmp)
    {   
	while (tmp->next)
	    tmp = tmp->next;
	tmp->next = new;
    }
    new->next = NULL;
    return (new);
}

static int	split_buff(t_buff **lst, char **line)
{
    char	    *left;
    char	    *right;
    int		    i;
    int		    j;
    t_buff	    *tmp;

    tmp = *lst;
    i = 0;
    if((tmp->str)[0] == '\0')
	return (0);
    j = ft_strlen(tmp->str);
    while ((tmp->str)[i] != '\n' && (tmp->str)[i])
	i++;
    if	(!(left = (char*)malloc(i + 1)))
	return (-1);
    ft_memcpy(left, tmp->str, i);
    left[i] = '\0';
    *line = left;
    if (i == j)
	return (0);
    if (!(right = (char*)malloc(j - i + 1)))
	return (-1);
    ft_memcpy(right, &((tmp->str)[i + 1]), j - i);
    right[j - i] = '\0';
    free(tmp->str);
    tmp->str = right;
    return (1);
}

int		get_next_line(const int fd, char **line)
{
    static t_buff   *lst;
    char	    buff[BUFF_SIZE + 1];
    t_buff	    *tlst;
    char	    *tmp;
    int		    ret;
    
    ret = 1;
    if (!lst)
	lst = add_list(&lst,fd);
    if (!(find_list(&tlst, lst, fd)))
	tlst = add_list(&lst, fd);
    while (!(ft_strchr(tlst->str, '\n')) && ret)
    {
	if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
	    return (-1);
	buff[ret] = '\0';
	tmp = tlst->str;
	tlst->str = ft_strjoin(tlst->str, buff);
	free(tmp);
    }
    split_buff(&tlst, line);
    if (ret == 0)
    {
	remove_list(&lst, fd);
	return (0);
    }
    return (1);
}


int		main(void)
{
    char	*line;
    char	*line1;
    char	*line2;
    char	*line3;
    int		fd;
    int		fd1;
    int		fd2;
    int		fd3;
    int		i;

    i = 0;
    fd = open("get_next_line.c", O_RDONLY);
    fd1 = open ("get_next_line.h", O_RDONLY);
    fd2 = open ("libft.h", O_RDONLY);
    fd3 = open ("test", O_RDONLY);
    //    while (get_next_line(fd, &line))
    //    {
    //	printf("%s\n", line);
    //	free(line);
    //    }
    while (i < 200)
    {
	if (get_next_line(fd, &line))
	{
	    printf("1-%s\n", line); 
	    free(line);
	}
	if (get_next_line(fd1, &line1))
	{
	    printf("2-%s\n", line1); 
	    free(line1);
	}
	if (get_next_line(fd2, &line2))
	{
	    printf("3-%s\n", line2); 
	    free(line2);
	}
	if (get_next_line(fd3, &line3))
	{
	    printf("4-%s\n", line3); 
	    free(line3);
	}
	i++;
    }
    return (0);
}
