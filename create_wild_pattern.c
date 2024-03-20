#include "h.h"


void create_node(char *str, char type, t_list **head)
{
	t_list * tmp;
	t_list * node;

	node = malloc(sizeof(t_list));
	if (!node)
		return;
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

char *handle_other_2(char *str, int *i)
{
	int j;
	int l;

	j = *i;
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		l = skip_quotes_i(str, i);
		return (strndup(&str[j + 1], l - 2));
	}
	else
	{
		while (str[*i] && str[*i] != '*' && str[*i] != '\"' && str[*i] != '\'')
			(*i) ++;
		return (strndup(&str[j], (*i) - (j)));
	}
}

void handle_other(char *str, int *i, t_list **head)
{
	char *tmp;
	char *tmp2;
	char *tmp3;

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

t_list* creat_wild(char *str)
{
	int i;
	t_list * head;
	t_list * tmp;

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

	return (head);
}


void free_list(t_list *head) {
    t_list *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->str);
        free(tmp);
    }
}

void free_array(char **arr) {
    char **tmp = arr;
    while (*tmp) {
        free(*tmp);
        tmp++;
    }
    free(arr);
}