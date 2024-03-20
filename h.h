
#ifndef H_H
# define H_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct s_list
{
	char *str;
	char type;
	struct s_list *next;
	struct s_list *prev;
} t_list;

char *ft_strstr(char *str, char *to_find);
int skip_quotes_i(char *str, int *i);
void create_node(char *str, char type, t_list **head);
char *handle_other_2(char *str, int *i);
void handle_other(char *str, int *i, t_list **head);
t_list* creat_wild(char *str);
char **lst_file(t_list *head);
void add_back_list(char ***arr, char *str);
int check_wild(char *str, t_list *head);
int compare_strings(char *str, t_list *tmp);

char	*ft_strjoin(char const *s1, char const *s2);
void free_array(char **arr);
void free_list(t_list *head);

#endif