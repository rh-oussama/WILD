#include "h.h"

int compare_strings(char *str, t_list *tmp)
{
	if (tmp->prev && tmp->next && tmp->prev->type == 'W' && tmp->next->type == 'W')
	{
		char *found = strstr(str, tmp->str);
		if (!found)
			return 0;
		str = found + strlen(tmp->str);
	}
	else if (tmp->prev && !tmp->next && tmp->prev->type == 'W')
	{
		if (strcmp(str + strlen(str) - strlen(tmp->str), tmp->str) != 0)
			return 0;
		str += strlen(str);
	}
	else if (tmp->next && !tmp->prev && tmp->next->type == 'W')
	{
		if (strncmp(str, tmp->str, strlen(tmp->str)) != 0)
			return 0;
		str += strlen(tmp->str);
	}

	return 1;
}

int check_wild(char *str, t_list *head)
{
	t_list * tmp;
	int i;

	i = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == 'W')
			i++;
		tmp = tmp->next;
	}

	if (i == 0)
		return (0);
	tmp = head;
	while (tmp)
	{
		if (!compare_strings(str, tmp))
			return 0;
		tmp = tmp->next;
	}

	return 1;
}

void add_back_list(char ***arr, char *str)
{
	char **tmp;
	char **tmp2;
	int i;

	tmp = *arr;
	i = 0;
	while (tmp && tmp[i++]);
	tmp2 = malloc(sizeof(char*) *(i + 2));
	if (!tmp2)
		return;
	i = 0;
	while (tmp && tmp[i])
	{
		tmp2[i] = tmp[i];
		i++;
	}

	tmp2[i] = strdup(str);
	tmp2[i + 1] = NULL;
	free(*arr);
	*arr = tmp2;
}

char **lst_file(t_list *head)
{
	char **arr;
	DIR	*dir;
	struct dirent * entry;

	dir = opendir(".");
	arr = NULL;
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
		{
			if (check_wild(entry->d_name, head) == 1)
				add_back_list(&arr, strdup(entry->d_name));
		}
	}
	closedir(dir);
	return (arr);
}

char **insert_wild(char **arr, char **arg, int j)
{
    int i = 0;
    int l = 0;
    char **tmp;

    while (arr && arr[i++])
        ;
    while (arg && arg[i++])
        ;
    tmp = malloc(sizeof(char *) * (i + 1));
    if (!tmp)
        return NULL;
    i = 0;
    while (arg && arg[i] && i < j)
    {
        tmp[i] = arg[i];
        i++;
    }
    l = 0;
    while (arr && arr[l])
        tmp[i++] = arr[l++];
    while (arg && arg[j])
        tmp[i++] = arg[j++];
    tmp[i] = NULL;

    return tmp;
}

void apply_wild_card(char ***arg)
{
    char **tmp;
    char **tmp2;
    int i = 0;
    t_list *head;

    while ((*arg) && (*arg)[i])
    {
        head = creat_wild((*arg)[i]);
        tmp = lst_file(head);
        if (tmp && (*tmp))
        {
            tmp2 = insert_wild(tmp, (*arg), i);
            free(*arg);
            (*arg) = tmp2;
        }
        free(tmp);
        free_list(head);
        i++;
    }
}

int main(int argc, char **argv)
{
    char **arra = malloc(sizeof(char*) * 4);
    if (!arra) {
        return 1;
    }

    arra[0] = strdup("ls");
    arra[1] = strdup("*");
    arra[2] = strdup("*");
    arra[3] = strdup("*");

    apply_wild_card(&arra);
		int i = 0;
    while (arra[i])
	 {
		printf("%s\n", arra[i]);
		free(arra[i]);
		i++;
	 }
	 free(arra);
	 

    return 0;
}