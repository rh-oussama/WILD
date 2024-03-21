/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:23:17 by oussama           #+#    #+#             */
/*   Updated: 2024/03/21 05:03:55 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h.h"

int	compare_strings(char **str, t_list *tmp)
{
	char	*found;

	if (tmp->prev && tmp->next && tmp->prev->type == 'W'
		&& tmp->next->type == 'W')
	{
		found = strstr(*str, tmp->str);
		if (!found)
			return (0);
		*str = found + strlen(tmp->str);
	}
	else if (tmp->prev && !tmp->next && tmp->prev->type == 'W')
	{
		if (strcmp(*str + strlen(*str) - strlen(tmp->str), tmp->str) != 0)
			return (0);
		*str += strlen(*str);
	}
	else if (tmp->next && !tmp->prev && tmp->next->type == 'W')
	{
		if (strncmp(*str, tmp->str, strlen(tmp->str)) != 0)
			return (0);
		*str += strlen(tmp->str);
	}
	return (1);
}

int	check_wild(char *str, t_list *head)
{
	t_list	*tmp;
	int		i;

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
		if (!compare_strings(&str, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	add_back_list(char ***arr, char *str)
{
	char	**tmp;
	char	**tmp2;
	int		i;

	tmp = *arr;
	i = 0;
	while (tmp && tmp[i++])
		;
	tmp2 = malloc(sizeof(char *) * (i + 2));
	if (!tmp2)
		return ;
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

char	**lst_file_helper(struct dirent *entry, t_list *head, int d_ir,
		char **arr)
{
	char	*tmp;

	if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")
		&& strncmp(entry->d_name, ".", 1))
	{
		if (check_wild(entry->d_name, head) == 1)
		{
			if (d_ir == 1 && entry->d_type == DT_DIR)
			{
				tmp = ft_strjoin(entry->d_name, "/");
				add_back_list(&arr, tmp);
				free(tmp);
			}
			else if (d_ir == 0)
				add_back_list(&arr, entry->d_name);
		}
	}
	return (arr);
}

char	**lst_file(t_list *head, int d_ir)
{
	char			**arr;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	arr = NULL;
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		arr = lst_file_helper(entry, head, d_ir, arr);
		entry = readdir(dir);
	}
	closedir(dir);
	return (arr);
}

void	inset_wild_helper(char **arr, char **arg, int *i, int *l)
{
	(*i) = 0;
	(*l) = 0;
	while (arr && arr[(*i)])
	{
		(*i)++;
	}
	while (arg && arg[(*l)])
	{
		(*l)++;
		(*i)++;
	}
	(*l) = 0;
}

void	insert_wild(char **arr, char ***arg, int j)
{
	int		i;
	int		l;
	char	**tmp;

	inset_wild_helper(arr, *arg, &i, &l);
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return ;
	i = 0;
	while ((*arg) && (*arg)[i] && i < j)
	{
		tmp[i] = (*arg)[i];
		i++;
	}
	l = 0;
	while (arr && arr[l])
		tmp[i++] = arr[l++];
	free((*arg)[j++]);
	while ((*arg) && (*arg)[j])
		tmp[i++] = (*arg)[j++];
	tmp[i] = NULL;
	free(*arg);
	(*arg) = tmp;
}

void	apply_wild_card(char ***arg)
{
	char	**tmp;
	int		dir;
	int		i;
	t_list	*head;

	i = 0;
	while ((*arg) && (*arg)[i])
	{
		dir = creat_wild((*arg)[i], &head);
		tmp = lst_file(head, dir);
		if (tmp && *tmp)
			insert_wild(tmp, arg, i);
		free(tmp);
		free_list(head);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char **arra = malloc(sizeof(char *) * 9);
	if (!arra)
	{
		return (1);
	}

	arra[0] = strdup("****/");
	arra[1] = NULL;

	apply_wild_card(&arra);
	int i = 0;
	while (arra[i])
	{
		printf("%s\n", arra[i]);
		free(arra[i]);
		i++;
	}

	free(arra);

	return (0);
}