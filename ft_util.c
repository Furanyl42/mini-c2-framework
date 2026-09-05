#include "ft_util.h"

void	errprint(const char *name, const char *error)
{
	fprintf(stderr, "[%s]: Error: %s\n", name, error);
}