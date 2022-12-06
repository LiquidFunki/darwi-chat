#ifndef LIBMX_H
#define LIBMX_H

#include <unistd.h>
#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
//#include <malloc/malloc.h> // TODO: uncomment
// utils pack

void mx_print_unicode(wchar_t c); // ready
void mx_print_strarr(char **arr, const char *delim); // ready // what about between elements of array
int mx_quicksort(char **arr, int left, int right); // ready
int mx_get_char_index(const char *str, char c); // ready
char *mx_strndup(const char *s1, size_t n); // ready
char *mx_strcat(char *restrict s1, const char *restrict s2); // ready // restrict?
int mx_get_substr_index(const char *str, const char *sub); // ready
char *mx_file_to_str(const char *file); // check on leaks // ready
char *mx_replace_substr(const char *str, const char *sub, const char *replace); // ready
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd); // ready
char *mx_strndup(const char *s1, size_t n); // ready


void mx_printchar(char c); // ready
void mx_printstr(const char *s); // ready
void mx_printint(int n); // ready
void mx_printerr(char *);
double mx_pow(double n, unsigned int pow); // ready
int mx_sqrt(int x); // ready
char *mx_nbr_to_hex(unsigned long nbr); // ready
unsigned long mx_hex_to_nbr(const char *hex); // ready
char *mx_itoa(int number); // ready
void mx_foreach(int *arr, int size, void (*f)(int)); // ready
int mx_binary_search(char **arr, int size, const char *s, int *count); // ready
int mx_bubble_sort(char **arr, int size); // ready

bool mx_isalpha(int c); // my
bool mx_isdigit(int c); // my
bool mx_islower(int c); // my
bool mx_isupper(int c); // my
bool mx_isspace(char c); // my
// end utils pack

// string pack

int mx_strlen(const char *s); // ready
void mx_swap_char(char *s1, char *s2); // ready
void mx_str_reverse(char *s); // ready
void mx_strdel(char **str); // ready
void mx_del_strarr(char ***arr); // ready
char *mx_strdup(const char *s1); // ready
char *mx_strcpy(char *dst, const char *src); // ready // without testing
char *mx_strncpy(char *dst, const char *src, int len); // ready // have questions
int mx_strcmp(const char *s1, const char *s2); // ready
int mx_strncmp(const char *s1, const char *s2, int n); // my
char *mx_strstr(const char *haystack, const char *needle); // ready
int mx_count_substr(const char *str, const char *sub); // ready
int mx_count_words(const char *str, char c); // ready
char *mx_strnew(const int size); // ready
char *mx_strtrim(const char *str); // ready
char *mx_del_extra_spaces(const char *str); // ready
char **mx_strsplit(const char *s, char c); // ready
char *mx_strjoin(const char *s1, const char *s2); // ready
char *mx_strchr(const char *s, int c); // my

// end string pack

// memory pack

void *mx_memset(void *b, int c, size_t len); // ready
void *mx_memcpy(void *__restrict__ dst, const void *__restrict__ src, size_t n); // ready
void *mx_memccpy(void *__restrict__ dst, const void *__restrict__ src, int c, size_t n); // added // check
int   mx_memcmp(const void *s1, const void *s2, size_t n); // added // check
void *mx_memchr(const void *s, int c, size_t n); // ready
void *mx_memrchr(const void *s, int c, size_t n); // ready
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len); // ready
void *mx_memmove(void *dst, const void *src, size_t len); // ready
void *mx_realloc(void *ptr, size_t size); // leaks check // ready

// end memory pack

// list pack

typedef struct s_list
{
    void *data;
    struct s_list *next;
}              t_list;

t_list *mx_create_node(void *data); // ready
void mx_push_front(t_list **list, void *data); // ready
void mx_push_back(t_list **list, void *data); // ready
void mx_pop_front(t_list **head); // ready
void mx_pop_back(t_list **head); // added // fixed errors with free
int mx_list_size(t_list *list); // ready
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)); // ready

// end list pack

#endif
