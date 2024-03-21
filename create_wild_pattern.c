/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wild_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 03:04:48 by oussama           #+#    #+#             */
/*   Updated: 2024/03/21 04:42:35 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h.h"

void	create_node(char *str, char type, t_list **head)
{
	t_list	*tmp;
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	if (type != 'W')
		node->str = str;
	else
		node->str = strdup(str);
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	if (*head == NULL)
		(*head) = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
}

char	*handle_other_2(char *str, int *i)
{
	int	j;
	int	l;

	j = *i;
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		l = skip_quotes_i(str, i);
		return (strndup(&str[j + 1], l - 2));
	}
	else
	{
		while (str[*i] && str[*i] != '*' && str[*i] != '\"' && str[*i] != '\'')
			(*i)++;
		return (strndup(&str[j], (*i) - (j)));
	}
}

void	handle_other(char *str, int *i, t_list **head)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	while (str[*i] != '*' && str[*i] != '\0')
	{
		tmp3 = handle_other_2(str, i);
		tmp2 = ft_strjoin(tmp, tmp3);
		free(tmp);
		free(tmp3);
		tmp = tmp2;
	}
	if (strlen(tmp) != 0)
		create_node(tmp, 'S', head);
}

int check_dir(t_list *head)
{
	char	*tmp2;
	int	i;
	int	dir;

	i = 0;
	dir = 0;
	while (head->next)
		head = head->next;
	if (head->type != 'S')
		return 0;
	i = strlen(head->str);
	i--;
	while (i >= 0 && (head->str)[i] == '/')
	{
		i--;
		dir++;
	}
	if (!dir)
		return (0);
	tmp2 = strndup(head->str, i + 1);
	free(head->str);
	head->str = tmp2;
	return (1);
}


int	creat_wild(char *str, t_list **h)
{
	int		i;
	t_list	*head;
	t_list	*tmp;

	i = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '*')
		{
			while (str[i] && str[i] == '*')
				i++;
			tmp = head;
			while (tmp && tmp->next != NULL)
				tmp = tmp->next;
			if (tmp == NULL || tmp->type == 'S')
				create_node("*", 'W', &head);
		}
		else
			handle_other(str, &i, &head);
	}
	(*h) = head;
	return (check_dir(head));
}

void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}
