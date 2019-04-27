#include "libft.h"
#include "get_next_line.h"

static t_bf	*new_buffer(int fd)
{
    t_bf    *new;

    if (!(new = (t_bf*)malloc(sizeof(t_bf))))
	return (0);
    new->fd = fd;
    if (!(new->buff = ft_strnew(0)))
    { 
	free(new);
	return (0);
    }
    return (new);
}

static void	del_buffer(void *content, size_t size)
{
    t_bf    *bf;

    bf = content;
    if (bf->buff)
	free(bf->buff);
    if (bf)
	free(bf);
    size = 0;
}

int		get_buffer(const int fd, t_bf **bf)
{
    t_bf		*tbf;
    char		*tmp;
    char		buff[BUFF_SIZE + 1];
    int			ret;

    ret = 1;
    tbf = *bf; 
    while (!(ft_strchr(tbf->buff, '\n')) && ret)
    {
	ret = read(fd, buff, BUFF_SIZE);
	buff[ret] = '\0';
	tmp = tbf->buff;
	if (!(tbf->buff = ft_strjoin(tbf->buff, buff)))
	    return (0);
	free(tmp);
    }
    return (1);
}

static int	split_buffer(t_bf **bf, char **line)
{
    char	    *left;
    char	    *right;
    int		    i;
    int		    j;
    t_bf	    *tbf;

    tbf = *bf;
    i = 0;
    if((tbf->buff)[0] == '\0')
	return (0);
    j = ft_strlen(tbf->buff);
    while ((tbf->buff)[i] != '\n' && (tbf->buff)[i])
	i++;
    if	(!(left = (char*)malloc(i + 1)))
	return (-1);
    ft_memcpy(left, tbf->buff, i);
    left[i] = '\0';
    *line = left;
    if (!(right = (char*)malloc(j - i + 1)))
	return (-1);
    ft_memcpy(right, &((tbf->buff)[i + 1]), j - i);
    right[j - i] = '\0';
    free(tbf->buff);
    tbf->buff = right;
    return (1);
}

t_list		*find_list(t_list *start, int fd)
{
    while (start)
    {
	if (((t_bf*)(start->content))->fd == fd)
	    return (start);
	start = start->next;
    }
    return (NULL);
}

static void	ft_list_remove(t_list **alst, t_list **list, void (*del)(void*, size_t))
{
    t_list	*current;
    t_list	*last;
    t_list	*tmp;

    current = *alst;
    while (current)
    {
	if (current == *list)
	{
	    if (current == *alst)
		*alst = current->next;
	    else
		last->next = current->next;
	    tmp = current;
	    current = current->next;
	    del(tmp->content, tmp->content_size);
	}
	else
	{
	    last = current;
	    current = current->next;
	}
    }
}

int		get_next_line(const int fd, char **line)
{
    static t_list	*list;
    t_list		*tlist;
    t_bf		*bf;
    t_bf		*tbf;
    char		buff[BUFF_SIZE];
    
    if (!fd || !line || read(fd, buff, 0) < 0)
	return (-1);

    if (!(tlist = find_list(list, fd)))
    {
	ft_lstadd(&list, (tlist = ft_lstnew((bf = new_buffer(fd)) , sizeof(t_bf))));
	free(bf);
    }
    tbf = tlist->content;
    if (!(get_buffer(fd, &tbf)))
	return (0);
    if (!(split_buffer(&tbf, line)))
    {
	printf("@");
//	ft_list_remove(&list, &tlist, &del_buffer);
	return (0);     
    }
    return (1);
}
