#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int checks;
static int failures;

#define CHECK(expr) do { \
	checks++; \
	if (!(expr)) { \
		fprintf(stderr, "line %d: %s\n", __LINE__, #expr); \
		failures++; \
	} \
} while (0)

static void characters(void)
{
	int c;

	for (c = 0; c < 128; c++)
	{
		CHECK(!!ft_isalpha(c) == !!isalpha(c));
		CHECK(!!ft_isdigit(c) == !!isdigit(c));
		CHECK(!!ft_isalnum(c) == !!isalnum(c));
		CHECK(!!ft_isprint(c) == !!isprint(c));
		CHECK(ft_isascii(c));
		CHECK(ft_toupper(c) == toupper(c));
		CHECK(ft_tolower(c) == tolower(c));
	}
	CHECK(!ft_isascii(-1) && !ft_isascii(128));
	CHECK(!ft_isalpha(0) && !ft_isdigit('a'));
}

static void memory(void)
{
	char a[16] = "abcdef";
	char b[16] = "abcdef";
	unsigned char *zero;

	CHECK(ft_memset(a, 'x', 3) == a);
	CHECK(memcmp(a, "xxxdef", 7) == 0);
	CHECK(ft_memcpy(a, b, 7) == a && memcmp(a, b, 7) == 0);
	CHECK(ft_memcpy(a, b, 0) == a);
	memmove(b + 1, b, 5);
	CHECK(ft_memmove(a + 1, a, 5) == a + 1);
	CHECK(memcmp(a, b, 7) == 0);
	memmove(b, b + 1, 5);
	ft_memmove(a, a + 1, 5);
	CHECK(memcmp(a, b, 7) == 0);
	CHECK(ft_memmove(a, a, 0) == a);
	ft_bzero(a, sizeof(a));
	CHECK(memcmp(a, (char[16]){0}, 16) == 0);
	CHECK(ft_memchr(b, 'a', 6) == memchr(b, 'a', 6));
	CHECK(ft_memchr(b, 'a', 0) == NULL);
	CHECK(ft_memcmp("a\0z", "a\0y", 3) > 0);
	CHECK(ft_memcmp("a", "b", 0) == 0);
	zero = ft_calloc(8, 1);
	CHECK(zero != NULL);
	if (zero != NULL)
		CHECK(memcmp(zero, (char[8]){0}, 8) == 0);
	free(zero);
	CHECK(ft_calloc(SIZE_MAX, 2) == NULL);
	free(ft_calloc(0, 8));
}

static void strings(void)
{
	char text[] = "abcabc";
	char dest[16] = "abc";
	char *copy;

	CHECK(ft_strlen("") == 0 && ft_strlen(text) == 6);
	CHECK(ft_strchr(text, 'a') == text);
	CHECK(ft_strrchr(text, 'a') == text + 3);
	CHECK(ft_strchr(text, 0) == text + 6);
	CHECK(ft_strrchr(text, 0) == text + 6);
	CHECK(ft_strchr(text, 'z') == NULL);
	CHECK(ft_strncmp("ab", "ac", 2) < 0);
	CHECK(ft_strncmp("ab", "ac", 1) == 0);
	CHECK(ft_strncmp("", "x", 0) == 0);
	CHECK(ft_strnstr(text, "", 0) == text);
	CHECK(ft_strnstr(text, "cab", 6) == text + 2);
	CHECK(ft_strnstr(text, "cab", 4) == NULL);
	CHECK(ft_strlcpy(dest, "hello", 0) == 5 && !strcmp(dest, "abc"));
	CHECK(ft_strlcpy(dest, "hello", 1) == 5 && dest[0] == 0);
	CHECK(ft_strlcpy(dest, "hello", 4) == 5 && !strcmp(dest, "hel"));
	CHECK(ft_strlcat(dest, "lo", 6) == 5 && !strcmp(dest, "hello"));
	CHECK(ft_strlcat(dest, "!", 3) == 4 && !strcmp(dest, "hello"));
	CHECK(ft_strlcat(dest, "!", 0) == 1 && !strcmp(dest, "hello"));
	copy = ft_strdup("");
	CHECK(copy != NULL && !strcmp(copy, ""));
	free(copy);
	CHECK(ft_atoi(" \t\n-2147483648") == INT_MIN);
	CHECK(ft_atoi("+2147483647") == INT_MAX);
	CHECK(ft_atoi("42tail") == 42 && ft_atoi("") == 0);
}

static char indexed(unsigned int index, char c)
{
	return (c + index);
}

static void indexed_inplace(unsigned int index, char *c)
{
	*c += index;
}

static void check_owned(char *value, const char *expected)
{
	CHECK(value != NULL && !strcmp(value, expected));
	free(value);
}

static void allocated_strings(void)
{
	char **words;
	char mutable[] = "aaa";
	int values[] = {0, -1, INT_MIN, INT_MAX};
	char expected[32];
	unsigned int i;

	check_owned(ft_substr("abc", 99, 3), "");
	check_owned(ft_substr("abc", 1, SIZE_MAX), "bc");
	check_owned(ft_substr("abc", 1, 0), "");
	check_owned(ft_strjoin("", "abc"), "abc");
	check_owned(ft_strtrim("  abc  ", " "), "abc");
	check_owned(ft_strtrim("xxx", "x"), "");
	check_owned(ft_strtrim("abc", ""), "abc");
	words = ft_split(",,one,,two,", ',');
	CHECK(words && words[0] && words[1]);
	if (words && words[0] && words[1])
		CHECK(!strcmp(words[0], "one") && !strcmp(words[1], "two") && !words[2]);
	if (words)
	{
		for (i = 0; words[i]; i++)
			free(words[i]);
		free(words);
	}
	words = ft_split("", ',');
	CHECK(words && !words[0]);
	free(words);
	words = ft_split("abc", '\0');
	CHECK(words && words[0] && !strcmp(words[0], "abc") && !words[1]);
	if (words)
	{
		free(words[0]);
		free(words);
	}
	for (i = 0; i < sizeof(values) / sizeof(values[0]); i++)
	{
		snprintf(expected, sizeof(expected), "%d", values[i]);
		check_owned(ft_itoa(values[i]), expected);
	}
	check_owned(ft_strmapi("aaa", indexed), "abc");
	ft_striteri(mutable, indexed_inplace);
	CHECK(!strcmp(mutable, "abc"));
}

static void descriptors(void)
{
	int channel[2];
	char buffer[64] = {0};
	ssize_t count;
	int opened;

	opened = pipe(channel);
	CHECK(opened == 0);
	if (opened != 0)
		return;
	ft_putchar_fd('A', channel[1]);
	ft_putstr_fd("hello", channel[1]);
	ft_putendl_fd("!", channel[1]);
	ft_putnbr_fd(INT_MIN, channel[1]);
	close(channel[1]);
	count = read(channel[0], buffer, sizeof(buffer));
	CHECK(count == 19 && !memcmp(buffer, "Ahello!\n-2147483648", 19));
	close(channel[0]);
}

static void *duplicate_content(void *content)
{
	return (ft_strdup(content));
}

static void increment(void *content)
{
	(*(char *)content)++;
}

static void lists(void)
{
	t_list *head = NULL;
	t_list *mapped;
	t_list *first = ft_lstnew(ft_strdup("a"));
	t_list *last = ft_lstnew(ft_strdup("b"));

	CHECK(ft_lstsize(NULL) == 0 && ft_lstlast(NULL) == NULL);
	CHECK(first && last && first->content && last->content);
	if (!first || !last || !first->content || !last->content)
		return;
	ft_lstadd_front(&head, first);
	ft_lstadd_back(&head, last);
	CHECK(head == first && ft_lstsize(head) == 2 && ft_lstlast(head) == last);
	ft_lstiter(head, increment);
	CHECK(!strcmp(head->content, "b") && !strcmp(last->content, "c"));
	mapped = ft_lstmap(head, duplicate_content, free);
	CHECK(mapped && mapped->next && ft_lstsize(mapped) == 2);
	if (mapped && mapped->next)
		CHECK(mapped->content != head->content && !strcmp(mapped->content, "b"));
	ft_lstclear(&mapped, free);
	ft_lstclear(&head, free);
	CHECK(head == NULL && mapped == NULL);
	ft_lstclear(&head, free);
	first = ft_lstnew(NULL);
	CHECK(first && first->content == NULL && first->next == NULL);
	ft_lstdelone(first, free);
}

int main(void)
{
	characters();
	memory();
	strings();
	allocated_strings();
	descriptors();
	lists();
	printf("libft: %d checks, %d failures\n", checks, failures);
	return (failures != 0);
}
