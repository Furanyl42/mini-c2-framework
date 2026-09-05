#ifndef FT_UTIL_H
# define FT_UTIL_H
# include <stdio.h>
# include <stdlib.h>
# include <curl/curl.h>
# include "libft.h"


typedef struct s_memory
{
	char	*memory;
	size_t	size;
}			t_memory;

void	errprint(const char *name, const char *error);
char    *ft_http_get_to_buffer(const char *url);
int     ft_simple_get(const char *url);
size_t  ft_write_callback(void *contents, size_t size, size_t nmemb, void *userp);
char    *ft_http_post(const char *url, const char *post_data);
char    *ft_fetch_command(const char *url, const char *client_id);
void	logme(int istittle, const char *message);
#endif 