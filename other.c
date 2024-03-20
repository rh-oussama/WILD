
#include "h.h"

char *ft_strstr(char *str, char *to_find)
{
	int str_index;
	int to_find_index;

	str_index = 0;
	to_find_index = 0;
	while (str[str_index] != '\0' && to_find[to_find_index] != '\0')
	{
		if (to_find[to_find_index] == str[str_index])
			to_find_index++;
		else
			to_find_index = 0;
		str_index++;
	}

	if (to_find_index == strlen(to_find))
		return (&str[str_index - to_find_index]);
	else
		return (NULL);
}

int skip_quotes_i(char *str, int *i)
{
	int count;
	char quote;

	count = 2;
	quote = str[*i];
	(*i) ++;
	while (str[*i] != quote && str[*i] != '\0')
	{
		(*i) ++;
		count++;
	}

	if (str[*i] == quote)
		(*i) ++;
	return (count);
}