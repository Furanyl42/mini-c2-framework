#include "ft_util.h"

size_t ft_write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t	realsize;
	t_memory *chunk;
	char *ptr;

	realsize = size * nmemb;
	chunk = (t_memory *)userp;
	ptr = realloc(chunk->memory, chunk->size + realsize + 1);
	if (!ptr)
	{
		errprint("realloc", "not enougn memory");
		return (-1);
	}
	chunk->memory = ptr;
	ft_memcpy(&(chunk->memory[chunk->size]), contents, realsize);
	chunk->size += realsize;
	chunk->memory[chunk->size] = 0;
	return (realsize);
}