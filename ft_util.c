#include "ft_util.h"

void	errprint(const char *name, const char *error)
{
	fprintf(stderr, "[MINI_C2] (%s): Error: %s\n", name, error);
}